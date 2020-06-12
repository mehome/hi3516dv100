#!/bin/sh

#set -e

# for debug
DEBUG_LOG_FILE='&2'
DEBUG_LOG_LEVEL=0

# ANSI COLORS
COLOR_CRE="[K"
COLOR_NORMAL="[0;39m"
COLOR_RED="[1;31m"
COLOR_GREEN="[1;32m"
COLOR_YELLOW="[1;33m"
COLOR_BLUE="[1;34m"
COLOR_MAGENTA="[1;35m"
COLOR_CYAN="[1;36m"
COLOR_WHITE="[1;37m"

# Shell command
TAR=tar
CP=/bin/cp
RM=/bin/rm
GREP=grep
SED=sed
MKDIR=mkdir
CHMOD=chmod
MV=mv
CD=cd
LN=ln
MAKE=make
MKNOD=mknod
PUSHD=pushd 
POPD=popd 
RMDIR=rmdir
DEPMOD=/sbin/depmod
RMDIR=rmdir
MKIMG=mkimage
PATCH=patch
DIFF=diff
TOUCH=touch
CAT=cat

e_blank='[        ][      ]*'
e_year='20[0-9][0-9]'
e_month='([1-9]|0[1-9]|1[0-2])'
e_day='([1-9]|0[1-9]|[12][0-9]|3[0-1])'
e_time='([01][0-9]|2[0-3]):[0-5][0-9]'
e_employid='[a-zA-Z][a-zA-Z]*[0-9]{4,}'

#$1: string
#$2: color
ECHO()
{
	[ -n "$2" ] && eval echo -n \"\${${2}}\";
	echo "${1}${COLOR_NORMAL}"
}

ERR()
{
	echo "${COLOR_RED} ERR: ${1}${COLOR_NORMAL}" >&2
}

WARN()
{
	echo "${COLOR_YELLOW}WARN: ${1}${COLOR_NORMAL}" >&2
}

# $1:
LOG()
{
	echo "$1"
}


#$1: string
#$2: level
DEBUG()
{
	local level=$2
	[ -z "$level" ] && { level=0; }
	[ $level -lt $DEBUG_LOG_LEVEL ] && return 0;

	echo "$COLOR_WHITE$1$COLOR_NORMAL" > $DEBUG_LOG_FILE
}

# $1: command
# $2: LR/CR steps
run_command_progress()
{
	local n=0
	local steps=$2
	local progress_bar=""
	local counter=0
	local files=0

	ECHO "run_command_progress: '$1'" 
	[ -z "$steps" ] && { steps=1; }

	[ -n "$3" ] && [ -d "$3" ] && { steps=`find $3 | wc -l`; steps=`expr $steps / 50`; }

	eval $1 | while read line
	do
		#((n++))
		#((files++))
		((++n))
		((++files))

		if [ $n -ge $steps ] ;
		then
			#((counter++))
			((++counter))
			if [ $counter -le 50 ] ;
			then
				progress_bar="$progress_bar#";
				printf "     --------------------------------------------------|\r[%03d]$progress_bar\r" $steps
			else
				printf "[%03d#$progress_bar|\r" `expr $files / 50`
			fi

			n=0
		fi
	done

	echo ""
}

# $1: command
# $2: total
# $3: command to calc totals
run_command_progress_float()
{
	local readonly RCP_RANGE=50
	local rcp_lines=0
	local rcp_nextpos=1
	local rcp_total=0
	local progress_bar=
	local rcp_prog=0
	local rcp_tmp=0
	local prog_bar_base=
	local rcp_percent=0

	ECHO "run_command_progress_float: '$1'" 

	if [ -n "$3" ] ;
	then
		echo -n "Initializing progress bar ..."
		rcp_total=`eval $3`;
		echo -n "\r"
		[ -z "$rcp_total" ] && rcp_total=1
	else
		[ -n "$2" ] && rcp_total=$2
	fi

	[ -z "$rcp_total" ] && rcp_total=1
	[ $rcp_total -le 0 ] && rcp_total=1

	prog_bar_base="[    ]"
	while [ $rcp_tmp -lt $RCP_RANGE ]
	do
		prog_bar_base="$prog_bar_base-"
		#((rcp_tmp++)) 
		((++rcp_tmp)) 
	done
	prog_bar_base="${prog_bar_base}|"
	printf "\r$prog_bar_base\r"

	set +e
	eval $1 | while read line
	do
		#((rcp_lines++))
		((++rcp_lines))

		if [ $rcp_lines -ge $rcp_nextpos ]
		then
			rcp_percent=`expr \( $rcp_lines \* 101 - 1 \) / $rcp_total `
			rcp_prog=`expr \( $rcp_lines \* \( $RCP_RANGE + 1 \) - 1 \) / $rcp_total `
			[ $rcp_prog -gt $RCP_RANGE ] && rcp_prog=$RCP_RANGE
			rcp_nextpos=`expr \( \( $rcp_percent + 1 \) \* $rcp_total \) / 100`
			[ $rcp_nextpos -gt $rcp_total ] && rcp_nextpos=$rcp_total

			rcp_tmp=0
			progress_bar=""
			while [ $rcp_tmp -lt $rcp_prog ]
			do
				progress_bar="$progress_bar#"
				((rcp_tmp++))
			done
			printf "\r$prog_bar_base\r[%3d%%]$progress_bar\r" $rcp_percent
		fi
	done
	set -e

	echo ""
}

#$1: path
abs_path()
{
	pushd "$1" >/dev/null
	[ $? -ne 0 ] && return 1;
	pwd
	popd >/dev/null
}

#$1: $cfg_moddir is multi
prepare_unpacking_cleanup()
{
	$CAT >> $HCM_SH_SDKINSTALL << EOF

ECHO "unpacking $cfg_moddir"
mkdir -pv $module_basedir
run_command_progress_float "tar -xvzf `sub_dir $dir_postbuild_srctarball $HCM_DESTDIR`/$module_dirname.tgz -C $module_basedir/" 0 \
	"tar -tzf `sub_dir $dir_postbuild_srctarball $HCM_DESTDIR`/$module_dirname.tgz | wc -l"
EOF

if [ -z "$1" ] ;
then
	$CAT >> $HCM_SH_SDKCLEANUP << EOF

ECHO "cleanup $cfg_moddir"
run_command_progress_float "rm $cfg_moddir -frv" 0 "find $cfg_moddir | wc -l"
EOF
else
	$CAT >> $HCM_SH_SDKCLEANUP << EOF

ECHO "cleanup $cfg_moddir"
pushd $module_basedir
run_command_progress_float "rm $cfg_moddir -frv" 0 "find $cfg_moddir | wc -l"
popd
EOF
fi

}

# $1: prefix
# $2..$n: dirs list
make_dirs()
{
	local make_dirs_count=2
	local make_dirs_dir=

	[ -z "$1" ] && { ERR "make_dirs mast have a prefix dir!"; return 1; }
	$MKDIR $1 -p

	while true
	do
		eval make_dirs_dir=\${$make_dirs_count}
		[ -z "$make_dirs_dir" ] && break;
		$MKDIR $1/$make_dirs_dir -p
		#((make_dirs_count++))
		((++make_dirs_count))
	done
}

check_dir_empty()
{
	[ -z "$1" ] && return 0;
	! [ -d $1 ] && return 0;
	[ -z "`find $1/ -maxdepth 1 -mindepth 1`" ] && return 0;

	return 1
}

# $1 - $2
# $3: frefix for '/', like "\\\\/"
sub_dir()
{
	local subdir=
	local dirA=`dirname $1/stub`
	local dirB=`dirname $2/stub`

	while [ "$dirA" != "$dirB" ] && [ "$dirA" != "." ] && [ "$dirA" != "/" ] 
	do
		if [ -z "$subdir" ] ; then
			subdir=`basename $dirA`
		else
			subdir=`basename $dirA`$3/$subdir
		fi
		dirA=`dirname $dirA`
	done

	[ -z "$subdir" ] && subdir=.

	dirname $subdir/stub
}

# $1: base dir
# $2: dest dir
# $3: frefix for '/', like "\\\\/"
base_offset_dir()
{
	local ofstdir=`sub_dir $2 $1`
	local bodofst=

	while [ "$ofstdir" != "." ] && [ "$ofstdir" != "/" ] 
	do
		if [ -z "$bodofst" ] ; then
			bodofst=..
		else
			bodofst=..$3/$bodofst
		fi
		ofstdir=`dirname $ofstdir`
	done

	dirname $bodofst/stub
}

#$1: dir
set_drv_kbuild()
{
	local cc_file=Makefile
	local mbdir= 

	for mbdir in $1 $1/*
	do
		if [ -f $mbdir/$cc_file ] ;
		then
			local kbuild_dir_adj="`base_offset_dir $HCM_DESTDIR $mbdir "\\\\"`\\/`echo "$HCM_SDKDIR_KBUILD" | \
				sed -n "s/\//\\\\\\\\\//gp"`"

			$SED -i "s/^KERNEL_MAKE[ \t]*:=.*/KERNEL_MAKE := -C $kbuild_dir_adj/" $mbdir/$cc_file
		fi
	done	
}

#$1: name
#$2: level
write_rootfs_level()
{
	local rlevel_config=$HCM_DESTDIR/$HCM_SDKDIR_RESOURCE/rlevel.config
	$TOUCH $rlevel_config
	[ -n "`grep "^\[[0-9A-Za-z][0-9A-Za-z\-]*\]	$1$" < $rlevel_config`" ] && { \
       		WARN "$rlevel_config already have item '$1'"
		return 0;
	}
	echo "[$2]	$1" >> $rlevel_config
}

#$1: 
remove_all_cvsdir()
{
	! [ -d "$1" ] && { WARN "'$1' not found when remove 'CVS' directories."; return ; }

	ECHO "Remove: 'CVS' directories in $1"
	find $1 -type d -name "CVS" | xargs rm -fr
}

#$1: strip command
#$2: file list
strip_elf()
{
	for file in $2
	do
		[ -z "`file $file | grep "ELF .* executable, .*, not stripped"`" ] && continue

		ECHO "$1 $file"
		$1 $file
	done
}

#$1: strip command
#$2: file list
strip_lib()
{
	for file in $2
	do
		[ -z "`file $file | grep "ELF .* shared object, .*, not stripped"`" ] && continue

		ECHO "strip not really done: $file"
	done
}

# $1: rootfs base
# $2: modules list
install_extern_kmod()
{
	local iek_installed_modules=
	local iek_dest_module=
	local iek_depend_info=
	local iek_install_base=

	pushd $1 >/dev/null
	iek_install_base=$PWD
	popd >/dev/null

	for iek_extmod in `find $2`
	do
		iek_dest_module=/$HCM_INROOTFS_EXTKMOD/`basename $iek_extmod`

		[ -f $HCM_DESTDIR/$HCM_KERNEL_INSTALL_RESOURCE/$iek_dest_module ] && \
			{ WARN "Extern module $iek_extmod conflict: $iek_dest_module"; sleep 1; }

		iek_installed_modules="$iek_installed_modules $iek_dest_module"
		$CP -uf $iek_extmod $HCM_DESTDIR/$HCM_KERNEL_INSTALL_RESOURCE/$iek_dest_module
	done

	pushd $HCM_DESTDIR/$HCM_KERNEL_INSTALL_RESOURCE >/dev/null

	ECHO "Generating modules dependency ..."
	$DEPMOD -ae -b ./ -r -F $HCM_DESTDIR/$HCM_SDKDIR_KBUILD/System.map $HCM_KERNEL_RELEASE

	for iek_extmod in $iek_installed_modules
	do
		iek_depend_info=`grep "^$iek_extmod:" < $HCM_DESTDIR/$HCM_KERNEL_INSTALL_RESOURCE/$HCM_INROOTFS_DEPKMOD/modules.dep | sed "s/\://"`
		for iek_extmod in $iek_depend_info
		do
			$CP -uf --parents .$iek_extmod $iek_install_base/
			[ x$cfg_install_strip == xyes ] && $HCM_CROSS_COMPILE-strip $iek_install_base$ikm_kmod -g -S -d

		done
	done

	popd >/dev/null
}

# $1: dest rootfs based
# $2: module list
install_kernel_module()
{
	local ikm_kmod_resdir=$HCM_DESTDIR/$HCM_KERNEL_INSTALL_RESOURCE
	local ikm_install_basedir=
	local ikm_kmod=

	pushd $1 >/dev/null
	ikm_install_basedir=$PWD
	popd  >/dev/null

	pushd $ikm_kmod_resdir >/dev/null
	$DEPMOD -ae -b ./ -r -F $HCM_DESTDIR/$HCM_SDKDIR_KBUILD/System.map $HCM_KERNEL_RELEASE

	while read ikm_kmod
	do
		ikm_depend_info=`grep "^$ikm_kmod:" < $HCM_DESTDIR/$HCM_KERNEL_INSTALL_RESOURCE/$HCM_INROOTFS_DEPKMOD/modules.dep | sed "s/\://"`
		for ikm_kmod in $ikm_depend_info
		do
			$CP -uf --parents .$ikm_kmod $ikm_install_basedir
			[ x$cfg_install_strip == xyes ] && $HCM_CROSS_COMPILE-strip $ikm_install_basedir$ikm_kmod -g -S -d
		done
	done << EOF
	`pushd $HCM_INROOTFS_KERNMOD >/dev/null; \
		eval find "$2" -type f -printf \"/$HCM_INROOTFS_KERNMOD/%p\\\n\"; \
		popd >/dev/null`
EOF

	popd >/dev/null
}

string_to_varname()
{
	echo "$1" | sed 's/[^a-zA-Z0-9_]/_/g'
}

patchset_get_param()
{
	echo "$1" | cut -d')' -f1 | sed 's/[\(\|]/ /g'
}

patchset_get_name()
{
	echo "$file" | cut -d')' -f2
}

