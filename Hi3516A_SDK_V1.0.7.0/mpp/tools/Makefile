ifeq ($(PARAM_FILE), )
     PARAM_FILE:=../Makefile.param
     include $(PARAM_FILE)
endif

SRC  := $(wildcard *.c)
OBJ  := $(SRC:%.c=%.o)

INC_FLAGS := -I$(REL_INC)
CFLAGS += -Wall -g -lpthread -ldl $(INC_FLAGS)

LIBS += $(REL_LIB)/lib_hiae.a
LIBS += $(REL_LIB)/libisp.a

LIBS += $(REL_LIB)/lib_hiawb.a
LIBS += $(REL_LIB)/lib_hiaf.a
LIBS += $(REL_LIB)/lib_hidefog.a

LIBS += $(REL_LIB)/libmpi.a


# sensor input type: ar130 mn34031
SNS:=$(MAKECMDGOALS)

CFLAGS += $(LIBS_CFLAGS)

ifeq ($(SNS),)
SNS:=mn34220
endif

ifeq ($(SNS), mn34220)
LIBS += $(REL_LIB)/libsns_mn34220.a
CFLAGS += -DSNS_MN34220
endif

ifeq ($(SNS), imx178)
LIBS += $(REL_LIB)/libsns_imx178.a
CFLAGS += -DSNS_IMX178
endif

ifeq ($(SNS), imx185)
LIBS += $(REL_LIB)/libsns_imx185.a
CFLAGS += -DSNS_IMX185
endif

ifeq ($(SNS), ar0130)
LIBS += $(REL_LIB)/libsns_ar0130_720p.a
CFLAGS += -DSNS_AR0130
endif

ifeq ($(SNS), ar0130_960p)                                                                                                               
LIBS += $(REL_LIB)/libsns_ar0130_960p.a
CFLAGS += -DSNS_AR0130_960P
endif

ifeq ($(SNS), 9m034)
LIBS += $(REL_LIB)/libsns_9m034.a
CFLAGS += -DSNS_9M034
endif

ifeq ($(SNS), 9m034_960p)
LIBS += $(REL_LIB)/libsns_9m034_960p.a
CFLAGS += -DSNS_9M034_960P
endif

ifeq ($(SNS), imx104)
LIBS += $(REL_LIB)/libsns_imx104.a
CFLAGS += -DSNS_IMX104
endif

ifeq ($(SNS), imx122)
LIBS += $(REL_LIB)/libsns_imx122.a
CFLAGS += -DSNS_IMX122
endif

ifeq ($(SNS), mn34031)
LIBS += $(REL_LIB)/libsns_mn34031_720p.a
CFLAGS += -DSNS_MN34031
endif

ifeq ($(SNS), ov9712)
LIBS += $(REL_LIB)/libsns_ov9712.a
CFLAGS += -DSNS_OV9712
endif

ifeq ($(SNS), mt9p006)
LIBS += $(REL_LIB)/libsns_mt9p006.a
CFLAGS += -DSNS_MT9P006
endif

ifeq ($(SNS), mt9v139)
LIBS += $(REL_LIB)/libsns_mt9v139_d1.a
CFLAGS += -DSNS_MT9V139_D1
endif

CFLAGS += -lm
TARGET := $(OBJ:%.o=%)

.PHONY : clean all $(SNS)

all: $(TARGET)

$(TARGET):%:%.o 
	$(CC) $(CFLAGS)  -o $@ $^ $(LIBS) $(AUDIO_LIBA) -Wl,-gc-sections
	@rm *.o
clean:
	@rm -f $(TARGET)
	@rm -f $(OBJ)
ifneq ($(SNS), clean)
$(SNS): all
	@echo
endif
