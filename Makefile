# ====================================================================
# Makefile - Tu dong hoa build Thu vien Static, Shared va Kiem thu
# ====================================================================

# Trinh bien dich va co bien dich
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c99
AR      := ar
ARFLAGS := rcs

# Ten cac thu vien va tep thuc thi
STATIC_LIB := libstrutils.a
SHARED_LIB := libstrutils.so
STATIC_EXE := main_static
SHARED_EXE := main_shared

# Danh sach object files
OBJS := strutils.o strutils_pic.o main.o

# Khai bao target gia
.PHONY: all static shared clean test help

# 1. Target mac dinh: build ca ban static va shared
all: static shared

# 2. Target chi build static
static: $(STATIC_EXE)

# 3. Target chi build shared
shared: $(SHARED_EXE)

# --- Quy tac lien ket tao file thuc thi ---

$(STATIC_EXE): main.o $(STATIC_LIB)
	$(CC) $(CFLAGS) main.o $(STATIC_LIB) -o $@

$(SHARED_EXE): main.o $(SHARED_LIB)
	$(CC) $(CFLAGS) main.o -L. -lstrutils -Wl,-rpath,. -o $@

# --- Quy tac dong goi thu vien ---

$(STATIC_LIB): strutils.o
	$(AR) $(ARFLAGS) $@ $^

$(SHARED_LIB): strutils_pic.o
	$(CC) -shared -o $@ $^

# --- Quy tac bien dich file ma nguon thanh object file (.o) ---

main.o: main.c strutils.h
	$(CC) $(CFLAGS) -c $< -o $@

strutils.o: strutils.c strutils.h
	$(CC) $(CFLAGS) -c $< -o $@

strutils_pic.o: strutils.c strutils.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# --- Target don dep file sinh ra ---
clean:
	rm -f $(OBJS) $(STATIC_LIB) $(SHARED_LIB) $(STATIC_EXE) $(SHARED_EXE) main_test
	@echo ">> Da don dep toan bo file build (.o, .a, .so, executable)."

# --- Target chay kiem thu tu dong ---
test: all
	@echo "=========================================="
	@echo ">> Chay kiem thu ban STATIC (main_static):"
	@echo "=========================================="
	./$(STATIC_EXE)
	@echo ""
	@echo "=========================================="
	@echo ">> Chay kiem thu ban SHARED (main_shared):"
	@echo "=========================================="
	./$(SHARED_EXE)