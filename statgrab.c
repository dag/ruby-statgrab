/* Copyright (C) 2008 Dag Odenhall <dag.odenhall@gmail.com>
 * Licensed under the Academic Free License version 3.0 */

#include <ruby.h>
#include <statgrab.h>

VALUE cStatgrab;
VALUE eStatgrabError;

static VALUE statgrab_initialize(VALUE self, VALUE args) {
  if(sg_init())
    rb_raise(eStatgrabError, "sg_init() failed: %s", sg_str_error(sg_get_error()));

  if(rb_ary_shift(args) != Qfalse)
    if(sg_drop_privileges())
      rb_raise(eStatgrabError, "sg_drop_privileges() failed: %s", sg_str_error(sg_get_error()));

  return self;
}

static VALUE statgrab_cpu_stats(VALUE self) {
  sg_cpu_stats *stats;
  VALUE info;

  stats = sg_get_cpu_stats();
  if(stats == NULL)
    rb_raise(eStatgrabError, "sg_get_cpu_stats() failed: %s", sg_str_error(sg_get_error()));

  info = rb_hash_new();
  rb_hash_aset(info, ID2SYM(rb_intern("user")), INT2NUM(stats->user));
  rb_hash_aset(info, ID2SYM(rb_intern("kernel")), INT2NUM(stats->kernel));
  rb_hash_aset(info, ID2SYM(rb_intern("idle")), INT2NUM(stats->idle));
  rb_hash_aset(info, ID2SYM(rb_intern("iowait")), INT2NUM(stats->iowait));
  rb_hash_aset(info, ID2SYM(rb_intern("swap")), INT2NUM(stats->swap));
  rb_hash_aset(info, ID2SYM(rb_intern("nice")), INT2NUM(stats->nice));
  rb_hash_aset(info, ID2SYM(rb_intern("systime")), INT2NUM(stats->systime));

  VALUE time_at;
  time_at = rb_funcall(rb_cTime, rb_intern("at"), 1, INT2NUM(stats->systime));
  rb_hash_aset(info, ID2SYM(rb_intern("time")), time_at);

  return info;
}

static VALUE statgrab_cpu_percents(VALUE self) {
  sg_cpu_percents *percents;
  VALUE info;

  percents = sg_get_cpu_percents();
  if(percents == NULL)
    rb_raise(eStatgrabError, "sg_get_cpu_percents() failed: %s", sg_str_error(sg_get_error()));

  info = rb_hash_new();
  rb_hash_aset(info, ID2SYM(rb_intern("user")), rb_float_new(percents->user));
  rb_hash_aset(info, ID2SYM(rb_intern("kernel")), rb_float_new(percents->kernel));
  rb_hash_aset(info, ID2SYM(rb_intern("idle")), rb_float_new(percents->idle));
  rb_hash_aset(info, ID2SYM(rb_intern("iowait")), rb_float_new(percents->iowait));
  rb_hash_aset(info, ID2SYM(rb_intern("swap")), rb_float_new(percents->swap));
  rb_hash_aset(info, ID2SYM(rb_intern("nice")), rb_float_new(percents->nice));
  rb_hash_aset(info, ID2SYM(rb_intern("time_taken")), INT2NUM(percents->time_taken));

  VALUE time_now;
  time_now = rb_funcall(rb_cTime, rb_intern("now"), 0);
  rb_hash_aset(info, ID2SYM(rb_intern("last_call")), rb_funcall(time_now, rb_intern("-"), 1, INT2NUM(percents->time_taken)));

  return info;
}

void Init_statgrab() {
  cStatgrab = rb_define_class("Statgrab", rb_cObject);
  eStatgrabError = rb_define_class("StatgrabError", rb_eException);
  rb_define_method(cStatgrab, "initialize", statgrab_initialize, -2);
  rb_define_method(cStatgrab, "cpu_stats", statgrab_cpu_stats, 0);
  rb_define_method(cStatgrab, "cpu_percents", statgrab_cpu_percents, 0);
}
