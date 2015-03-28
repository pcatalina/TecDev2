###############################################################################
#			PARAMETERS
###############################################################################

OUTPUT_NAME=poly
CONFIGNAME=debug

# input
INCLUDE_DIRS = src
SOURCE_DIR = src
DOCS_DIR = docs/html

# output
BIN_DIR = bin
OBJ_DIR = obj

# toolchain executables
CC = gcc
LD = gcc
AR = ar
AS = as
MKDIR = mkdir -p
CP = cp

# file types to consider
HEADERS_EXTENSIONS = .h
SOURCES_EXTENSIONS = .c

###############################################################################
#			FLAGS
###############################################################################

# compiler settings
CFLAGS += -Wall -Wextra -pedantic -std=c11
CFLAGS_DEBUG += -g -O0
CFLAGS_RELEASE += -O3

# linker settings
LDFLAGS += -lm
LDFLAGS_DEBUG +=
LDFLAGS_RELEASE +=


ifeq ($(CONFIGNAME), debug)
	CFLAGS += $(CFLAGS_DEBUG)
	LDFLAGS += $(LDFLAGS_DEBUG)
endif

ifeq ($(CONFIGNAME), release)
	CFLAGS += $(CFLAGS_RELEASE)
	LDFLAGS += $(LDFLAGS_RELEASE)
endif

###############################################################################
#			OBJ path pre-baking
###############################################################################

#prepare stuff
BinaryFilePath = $(BIN_DIR)/$(OUTPUT_NAME)
SourceFilesWithPaths = $(MORE_SOURCE_FILES) $(foreach d,$(SOURCE_DIR),$(wildcard $(addprefix $(d)/*,$(SOURCES_EXTENSIONS))))

# strip path
SOURCE_FILES :=  $(notdir $(SourceFilesWithPaths))

# strip extension
SOURCE_FILES_NAMES :=  $(basename $(SOURCE_FILES))

#generate obj files names
ObjFiles = $(addsuffix .o, $(SOURCE_FILES_NAMES))
ObjFiles := $(addprefix $(OBJ_DIR)/, $(ObjFiles))
IncludeDirs = $(foreach inc, $(INCLUDE_DIRS), $(addprefix -I, $()))

###############################################################################
#			TARGETS
###############################################################################

.PHONY: all force

all: ${BinaryFilePath}

# linking
${BinaryFilePath}: ${OBJ_DIR} ${ObjFiles} ${BIN_DIR}
	-${LD} ${LDFLAGS} ${ObjFiles} ${LIBS} -o $@

# compilation
${ObjFiles}: ${OBJ_DIR}/%.o: ${SOURCE_DIR}/%.c
	-${CC} ${CFLAGS} ${IncludeDirs} -MMD -c $< -o $@

# directories
${BIN_DIR}:
	${MKDIR} ${BIN_DIR}

${OBJ_DIR}:
	${MKDIR} ${OBJ_DIR}

clean:
	-rm -rf ${BIN_DIR}
	-rm -rf ${OBJ_DIR}
	-rm -rf ${DOCS_DIR}

docs: force
	-rm -rf ${DOCS_DIR}
	doxygen ./docs/Doxyfile
	${CP} -f  ./docs/intersection.svg ${DOCS_DIR}

-include ${OBJ_DIR}/*.d
	