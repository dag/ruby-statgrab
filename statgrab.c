#include <ruby.h>
#include <statgrab.h>

VALUE cStatgrab;

static VALUE statgrab_init(VALUE self) {
  if(!sg_init())
    return Qtrue;
  else
    return Qfalse;
}

static VALUE statgrab_drop_privileges(VALUE self) {
  if(!sg_drop_privileges())
    return Qtrue;
  else
    return Qfalse;
}

static VALUE statgrab_cpu_percents(VALUE self) {
  sg_cpu_percents *percents;
  VALUE info;

  percents = sg_get_cpu_percents();
  info = rb_hash_new();

  rb_hash_aset(info, ID2SYM(rb_intern("user")), rb_float_new(percents->user));
  rb_hash_aset(info, ID2SYM(rb_intern("kernel")), rb_float_new(percents->kernel));
  rb_hash_aset(info, ID2SYM(rb_intern("idle")), rb_float_new(percents->idle));
  rb_hash_aset(info, ID2SYM(rb_intern("iowait")), rb_float_new(percents->iowait));
  rb_hash_aset(info, ID2SYM(rb_intern("swap")), rb_float_new(percents->swap));
  rb_hash_aset(info, ID2SYM(rb_intern("nice")), rb_float_new(percents->nice));
  rb_hash_aset(info, ID2SYM(rb_intern("time_taken")), rb_float_new(percents->time_taken));

  return info;
}

void Init_statgrab() {
  cStatgrab = rb_define_module("Statgrab");
  rb_define_module_function(cStatgrab, "init", statgrab_init, 0);
  rb_define_module_function(cStatgrab, "drop_privileges", statgrab_drop_privileges, 0);
  rb_define_module_function(cStatgrab, "cpu_percents", statgrab_cpu_percents, 0);
}
