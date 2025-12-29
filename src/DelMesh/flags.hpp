#include <gflags/gflags.h>

DEFINE_bool(test, true, "This is a test");

DEFINE_string(input_path, "", "path to input point file");

DEFINE_string(output_path, "",
              "path to directory where output files will be written");
