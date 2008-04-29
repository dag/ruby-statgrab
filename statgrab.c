/* Copyright (C) 2008 Dag Odenhall <dag.odenhall@gmail.com>
 * Licensed under the Academic Free License version 3.0 */

#include <ruby.h>
#include <statgrab.h>

VALUE cStatgrab;

static VALUE statgrab_initialize(VALUE self, VALUE args) {
  if(sg_init())
    rb_raise(rb_eRuntimeError, "sg_init failed");

  if(rb_ary_shift(args) != Qfalse)
    if(sg_drop_privileges())
      rb_raise(rb_eRuntimeError, "sg_drop_privileges failed");

  return self;
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
  cStatgrab = rb_define_class("Statgrab", rb_cObject);
  rb_define_method(cStatgrab, "initialize", statgrab_initialize, -2);
  rb_define_method(cStatgrab, "cpu_percents", statgrab_cpu_percents, 0);
}
