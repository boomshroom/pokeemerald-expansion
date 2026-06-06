#ifdef __SANITIZE_UNDEFINED__

#include "gba/isagbprint.h"

struct ubsan_source_location
{
	const char* filename;
	uint32_t line;
	uint32_t column;
};

struct ubsan_type_descriptor
{
	uint16_t type_kind;
	uint16_t type_info;
	char type_name[];
};

typedef uintptr_t ubsan_value_handle_t;

static const struct ubsan_source_location unknown_location =
{
	"<unknown file>",
	0,
	0,
};

#define HANDLE0(name) \
void __ubsan_handle_##name (void* data_raw) { \
  struct ubsan_source_location * location = (struct ubsan_source_location *) data_raw; \
  DebugAssert(location->filename, location->line, #name, FALSE); \
}

#define HANDLE1(name) \
void __ubsan_handle_##name (void* data_raw, void* arg1) { \
  struct ubsan_source_location * location = (struct ubsan_source_location *) data_raw; \
  DebugAssert(location->filename, location->line, #name, FALSE); \
}

#define HANDLE2(name) \
void __ubsan_handle_##name (void* data_raw, void* arg1, void* arg2) { \
  struct ubsan_source_location * location = (struct ubsan_source_location *) data_raw; \
  DebugAssert(location->filename, location->line, #name, FALSE); \
}

// HANDLE1(type_mismatch_v1)
HANDLE1(out_of_bounds)
HANDLE2(pointer_overflow)
HANDLE2(add_overflow)
HANDLE2(sub_overflow)
HANDLE2(mul_overflow)
HANDLE2(divrem_overflow)
HANDLE2(shift_out_of_bounds)
HANDLE0(nonnull_arg)
HANDLE1(vla_bound_not_positive)
HANDLE1(negate_overflow)

struct ubsan_type_mismatch_v1_data
{
	struct ubsan_source_location location;
	struct ubsan_type_descriptor* type;
	unsigned char log_alignment;
	unsigned char type_check_kind;
};

static const char *const sTypeCheckKinds[] = {
    "load of", "store to", "reference binding to", "member access within",
    "member call on", "constructor call on", "downcast of", "downcast of",
    "upcast of", "cast to virtual base of", "_Nonnull binding to",
    "dynamic operation on"
};

void __ubsan_handle_type_mismatch_v1 (void* data_raw, void* pointer_raw) { \
  struct ubsan_type_mismatch_v1_data * data = (struct ubsan_type_mismatch_v1_data *) data_raw;
  if (data->location.line == 687 && data->type_check_kind == 0) return;
  ubsan_value_handle_t pointer = (ubsan_value_handle_t) pointer_raw;
  uintptr_t alignment = (uintptr_t) 1UL << data->log_alignment;
  const char* violation = "type mismatch";
  if ( !pointer ) violation = "null pointer access";
  else if ( alignment && (pointer & (alignment - 1)) ) violation = "unaligned access";
  DebugPrintf(
      "[%s:%d] %s with %s type %s at %X",
      data->location.filename,
      data->location.line,
      violation,
      sTypeCheckKinds[data->type_check_kind],
      data->type->type_name,
      pointer
  );
}

void __ubsan_handle_builtin_unreachable(void* data_raw) {
  struct ubsan_source_location * location = (struct ubsan_source_location *) data_raw;
  DebugAssert(location->filename, location->line, "builtin_unreachable", TRUE);
  for (;;) {
    asm volatile("");
  }
}

#endif
