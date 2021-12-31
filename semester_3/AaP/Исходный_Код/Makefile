.PHONY: all clean cleanall lines



EXEC_PATH = exec
INCLUDE_PATH = include

SRC_PATH  = src
SRC_CORE_PATH = $(SRC_PATH)/core
SRC_TUI_PATH = $(SRC_PATH)/tui



CORE_FILES = $(addprefix $(SRC_CORE_PATH)/,\
	$(addprefix date/,\
		date.c \
	)\
	$(addprefix file_system/,\
		files.c \
		csv_files.c \
		bin_files.c \
		text_files.c \
	)\
	$(addprefix lists/,\
		lists.c \
		lists_cmp_elems.c \
		lists_sort.c \
	)\
	$(addprefix non-standart_funcs/,\
		wcs_converters.c \
		cmp_functions.c \
		checker.c \
	)\
	additional_task.c \
)

TUI_FILES = $(addprefix $(SRC_TUI_PATH)/,\
	$(addprefix popups/,\
		pattern_functions.c \
		popup_text_message.c \
		popup_select.c \
		popup_form.c \
		popup_date.c \
		popup_element_info.c \
	)\
	$(addprefix menu/,\
		menu.c \
	)\
	$(addprefix forms/,\
		forms.c \
	)\
	$(addprefix table/,\
		table.c \
	)\
	$(addprefix windows/,\
		show_element_info_window.c \
	)\
)


PROG_NAME = program
GCC = gcc
CFLAGS = -I $(INCLUDE_PATH) -O2 -pipe -march=native
CLIBS = -lpanelw -lncursesw



MAIN_FILE = main.c

all: $(PROG_NAME)
clean:
	find . -name "*.o" | while read -r file; do rm "$$file"; done
cleanall: clean
	find . -name "*.a" | while read -r file; do rm "$$file"; done
	if [ -f "$(PROG_NAME)" ]; then rm -rf "$(PROG_NAME)"; fi
lines:
	wc --lines `find . -name "*.h"` `find . -name "*.c"`

# $(PROG_NAME): $(SRC_PATH)/$(subst .c,.o,$(MAIN_FILE)) $(SRC_PATH)/libcore.a $(SRC_PATH)/libtui.a
#	$(GCC) $(CFLAGS) -o $@ $^ $(CLIBS)

$(PROG_NAME): $(subst .c,.o,$(SRC_PATH)/$(MAIN_FILE) $(CORE_FILES) $(TUI_FILES))
	$(GCC) $(CFLAGS) -o $@ $^ $(CLIBS)

%.o: %.c
	$(GCC) -c $(CFLAGS) -o $@ $^ $(CLIBS)

$(SRC_PATH)/libcore.a: $(subst .c,.o,$(CORE_FILES))
	ar rc $@ $^
	ranlib $@

$(SRC_PATH)/libtui.a: $(subst .c,.o,$(TUI_FILES))
	ar rc $@ $^
	ranlib $@
