include ../common.mk

OUTDIR = ../OutputDirectory/$(PLATFORM_NAME)

VER_MAJ   = $(shell grep -m 1 VER_MAJ ../makefile | sed 's/^.*=\s*//g')
VER_MIN   = $(shell grep -m 1 VER_MIN ../makefile | sed 's/^.*=\s*//g')
VER_PATCH = $(shell grep -m 1 VER_PATCH ../makefile | sed 's/^.*=\s*//g')

LIBNAME   = libarena$(D).so
SONAME    = ${LIBNAME}.${VER_MAJ}
TARGETLIB = ${SONAME}.${VER_MIN}.${VER_PATCH}

INCLUDE= -Iinclude           \
         -I../GenTL/include  \
         $(INC_BOOST_PATH)   \
         $(INC_GENICAM_PATH) \
         $(INC_IPP_PATH)     \
         $(INC_OPENCV_PATH)

CFLAGS=-Wall -Werror -std=c++11 -fPIC -Wno-unknown-pragmas $(PLATFORM_DEFINES)

LDFLAGS = -shared \
          -Wl,--whole-archive \
          $(BOOST_PATH_ROOT)/$(BOOST_LIB_DIR_NAME)/libboost_thread.a \
		  $(BOOST_PATH_ROOT)/$(BOOST_LIB_DIR_NAME)/libboost_system.a \
          -Wl,--no-whole-archive \
          -Wl,-Bstatic \
          $(LIB_IPP_STATIC) \
          -Wl,-Bdynamic \
          -Wl,-soname,$(SONAME)

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(OBJS:%.o=%.d)


.PHONY: all
all: release debug debug_test

.PHONY: release
release: CFLAGS += -O2
release: XML_DIR = $(OUTDIR)/$(EXE_DIR_PREFIX)Release/xml
release: build_target

.PHONY: debug
debug: D = d
debug: CFLAGS += -g -DDEBUG
debug: build_target

.PHONY: debug_test
debug_test: D = d
debug_test: CFLAGS += -g -DDEBUG -D_ARENA_UNIT_TEST_API -D_EXPORT_ARENA_UNIT_TEST_API -DARENA_EXPORTS
debug_test: INCLUDE += $(INC_GMOCK_PATH) $(INC_GTEST_PATH)
debug_test: build_target

.PHONY: build_target
build_target: $(OBJS)
	${CC} ${INCLUDE} -o $(TARGETLIB) $^ $(LDFLAGS) -Wl,--version-script=libarena.version
	-ln -sf $(TARGETLIB) $(SONAME)
	-ln -sf $(TARGETLIB) $(LIBNAME)
	-mkdir -p $(OUTDIR)/$(LIB_DIR_NAME)
	cp -d $(LIBNAME)* $(OUTDIR)/$(LIB_DIR_NAME)
	-mkdir -p ../include/Arena
	cp include/* ../include/Arena

.PHONY: clean
clean: clean_rel clean_deb

.PHONY: clean_rel
clean_rel:
	-${RM} ${TARGETLIB} ${SONAME} ${LIBNAME} ${OBJS} ${DEPS}

.PHONY: clean_deb
clean_deb: D = d
clean_deb:
	-$(RM) $(TARGETLIB) $(SONAME) $(LIBNAME) $(OBJS) $(DEPS)

%.o: %.cpp
	${CC} ${INCLUDE} -o $@ $< -c ${CFLAGS}

${DEPS}: %.cpp
	${CC} ${CLAGS} ${INCLUDE} -MM $< >$@

-include $(OBJS:.o=.d)
