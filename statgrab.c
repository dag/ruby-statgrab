/*
 *
 * Copyright 2008 Dag Odenhall <dag.odenhall@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <ruby.h>
#include <statgrab.h>

VALUE cStatgrab;
VALUE eStatgrabException;
VALUE eStatgrabAsprintfError;
VALUE eStatgrabDevicesError;
VALUE eStatgrabDevstatGetdevsError;
VALUE eStatgrabDevstatSelectdevsError;
VALUE eStatgrabDiskinfoError;
VALUE eStatgrabEnoentError;
VALUE eStatgrabGetifaddrsError;
VALUE eStatgrabGetmntinfoError;
VALUE eStatgrabGetpagesizeError;
VALUE eStatgrabHostError;
VALUE eStatgrabKstatDataLookupError;
VALUE eStatgrabKstatLookupError;
VALUE eStatgrabKstatOpenError;
VALUE eStatgrabKstatReadError;
VALUE eStatgrabKvmGetswapinfoError;
VALUE eStatgrabKvmOpenfilesError;
VALUE eStatgrabMallocError;
VALUE eStatgrabMemstatusError;
VALUE eStatgrabOpenError;
VALUE eStatgrabOpendirError;
VALUE eStatgrabParseError;
VALUE eStatgrabPdhaddError;
VALUE eStatgrabPdhcollectError;
VALUE eStatgrabPdhopenError;
VALUE eStatgrabPdhreadError;
VALUE eStatgrabPermissionError;
VALUE eStatgrabPstatError;
VALUE eStatgrabSetegidError;
VALUE eStatgrabSeteuidError;
VALUE eStatgrabSetmntentError;
VALUE eStatgrabSocketError;
VALUE eStatgrabSwapctlError;
VALUE eStatgrabSysconfError;
VALUE eStatgrabSysctlError;
VALUE eStatgrabSysctlbynameError;
VALUE eStatgrabSysctlnametomibError;
VALUE eStatgrabUnameError;
VALUE eStatgrabUnsupportedError;
VALUE eStatgrabXswVerMismatchError;

static void statgrab_handle_error() {
  sg_error err_num;
  err_num = sg_get_error();

  switch(err_num) {
    case SG_ERROR_NONE:
      return;
    case SG_ERROR_ASPRINTF:
      rb_raise(eStatgrabAsprintfError, "%s", sg_str_error(err_num));
    case SG_ERROR_DEVICES:
      rb_raise(eStatgrabDevicesError, "%s", sg_str_error(err_num));
    case SG_ERROR_DEVSTAT_GETDEVS:
      rb_raise(eStatgrabDevstatGetdevsError, "%s", sg_str_error(err_num));
    case SG_ERROR_DEVSTAT_SELECTDEVS:
      rb_raise(eStatgrabDevstatSelectdevsError, "%s", sg_str_error(err_num));
    case SG_ERROR_DISKINFO:
      rb_raise(eStatgrabDiskinfoError, "%s", sg_str_error(err_num));
    case SG_ERROR_ENOENT:
      rb_raise(eStatgrabEnoentError, "%s", sg_str_error(err_num));
    case SG_ERROR_GETIFADDRS:
      rb_raise(eStatgrabGetifaddrsError, "%s", sg_str_error(err_num));
    case SG_ERROR_GETMNTINFO:
      rb_raise(eStatgrabGetmntinfoError, "%s", sg_str_error(err_num));
    case SG_ERROR_GETPAGESIZE:
      rb_raise(eStatgrabGetpagesizeError, "%s", sg_str_error(err_num));
    case SG_ERROR_HOST:
      rb_raise(eStatgrabHostError, "%s", sg_str_error(err_num));
    case SG_ERROR_KSTAT_DATA_LOOKUP:
      rb_raise(eStatgrabKstatDataLookupError, "%s", sg_str_error(err_num));
    case SG_ERROR_KSTAT_LOOKUP:
      rb_raise(eStatgrabKstatLookupError, "%s", sg_str_error(err_num));
    case SG_ERROR_KSTAT_OPEN:
      rb_raise(eStatgrabKstatOpenError, "%s", sg_str_error(err_num));
    case SG_ERROR_KSTAT_READ:
      rb_raise(eStatgrabKstatReadError, "%s", sg_str_error(err_num));
    case SG_ERROR_KVM_GETSWAPINFO:
      rb_raise(eStatgrabKvmGetswapinfoError, "%s", sg_str_error(err_num));
    case SG_ERROR_KVM_OPENFILES:
      rb_raise(eStatgrabKvmOpenfilesError, "%s", sg_str_error(err_num));
    case SG_ERROR_MALLOC:
      rb_raise(eStatgrabMallocError, "%s", sg_str_error(err_num));
    case SG_ERROR_MEMSTATUS:
      rb_raise(eStatgrabMemstatusError, "%s", sg_str_error(err_num));
    case SG_ERROR_OPEN:
      rb_raise(eStatgrabOpenError, "%s", sg_str_error(err_num));
    case SG_ERROR_OPENDIR:
      rb_raise(eStatgrabOpendirError, "%s", sg_str_error(err_num));
    case SG_ERROR_PARSE:
      rb_raise(eStatgrabParseError, "%s", sg_str_error(err_num));
    case SG_ERROR_PDHADD:
      rb_raise(eStatgrabPdhaddError, "%s", sg_str_error(err_num));
    case SG_ERROR_PDHCOLLECT:
      rb_raise(eStatgrabPdhcollectError, "%s", sg_str_error(err_num));
    case SG_ERROR_PDHOPEN:
      rb_raise(eStatgrabPdhopenError, "%s", sg_str_error(err_num));
    case SG_ERROR_PDHREAD:
      rb_raise(eStatgrabPdhreadError, "%s", sg_str_error(err_num));
    case SG_ERROR_PERMISSION:
      rb_raise(eStatgrabPermissionError, "%s", sg_str_error(err_num));
    case SG_ERROR_PSTAT:
      rb_raise(eStatgrabPstatError, "%s", sg_str_error(err_num));
    case SG_ERROR_SETEGID:
      rb_raise(eStatgrabSetegidError, "%s", sg_str_error(err_num));
    case SG_ERROR_SETEUID:
      rb_raise(eStatgrabSeteuidError, "%s", sg_str_error(err_num));
    case SG_ERROR_SETMNTENT:
      rb_raise(eStatgrabSetmntentError, "%s", sg_str_error(err_num));
    case SG_ERROR_SOCKET:
      rb_raise(eStatgrabSocketError, "%s", sg_str_error(err_num));
    case SG_ERROR_SWAPCTL:
      rb_raise(eStatgrabSwapctlError, "%s", sg_str_error(err_num));
    case SG_ERROR_SYSCONF:
      rb_raise(eStatgrabSysconfError, "%s", sg_str_error(err_num));
    case SG_ERROR_SYSCTL:
      rb_raise(eStatgrabSysctlError, "%s", sg_str_error(err_num));
    case SG_ERROR_SYSCTLBYNAME:
      rb_raise(eStatgrabSysctlbynameError, "%s", sg_str_error(err_num));
    case SG_ERROR_SYSCTLNAMETOMIB:
      rb_raise(eStatgrabSysctlnametomibError, "%s", sg_str_error(err_num));
    case SG_ERROR_UNAME:
      rb_raise(eStatgrabUnameError, "%s", sg_str_error(err_num));
    case SG_ERROR_UNSUPPORTED:
      rb_raise(eStatgrabUnsupportedError, "%s", sg_str_error(err_num));
    case SG_ERROR_XSW_VER_MISMATCH:
      rb_raise(eStatgrabXswVerMismatchError, "%s", sg_str_error(err_num));
  }
}

static VALUE statgrab_initialize(VALUE self, VALUE args) {
  if(sg_init())
    statgrab_handle_error();

  if(rb_ary_shift(args) != Qfalse && sg_drop_privileges())
    statgrab_handle_error();

  return self;
}

static VALUE statgrab_cpu_stats(VALUE self) {
  sg_cpu_stats *stats;
  VALUE info;

  stats = sg_get_cpu_stats();
  if(stats==NULL)
    statgrab_handle_error();

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

static VALUE statgrab_cpu_stats_diff(VALUE self) {
  sg_cpu_stats *stats;
  VALUE info;

  stats = sg_get_cpu_stats_diff();
  if(stats==NULL)
    statgrab_handle_error();

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
  if(percents==NULL)
    statgrab_handle_error();

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

static VALUE statgrab_disk_io_stats(VALUE self) {
  int entries, i;
  sg_disk_io_stats *stats;
  VALUE arr, info;

  stats = sg_get_disk_io_stats(&entries);
  if(stats==NULL)
    statgrab_handle_error();

  arr = rb_ary_new();
  for(i = 0; i < entries; i++) {
    info = rb_hash_new();
    rb_hash_aset(info, ID2SYM(rb_intern("disk_name")), rb_str_new2(stats[i].disk_name));
    rb_hash_aset(info, ID2SYM(rb_intern("read_bytes")), INT2NUM(stats[i].read_bytes/1024));
    rb_hash_aset(info, ID2SYM(rb_intern("write_bytes")), INT2NUM(stats[i].write_bytes/1024));
    rb_hash_aset(info, ID2SYM(rb_intern("systime")), INT2NUM(stats[i].systime));

    VALUE time_at;
    time_at = rb_funcall(rb_cTime, rb_intern("at"), 1, INT2NUM(stats[i].systime));
    rb_hash_aset(info, ID2SYM(rb_intern("time")), time_at);

    rb_ary_push(arr, info);
  }

  return arr;
}

static VALUE statgrab_disk_io_stats_diff(VALUE self) {
  int entries, i;
  sg_disk_io_stats *stats;
  VALUE arr, info;

  stats = sg_get_disk_io_stats_diff(&entries);
  if(stats==NULL)
    statgrab_handle_error();

  arr = rb_ary_new();
  for(i = 0; i < entries; i++) {
    info = rb_hash_new();
    rb_hash_aset(info, ID2SYM(rb_intern("disk_name")), rb_str_new2(stats[i].disk_name));
    rb_hash_aset(info, ID2SYM(rb_intern("read_bytes")), INT2NUM(stats[i].read_bytes/1024));
    rb_hash_aset(info, ID2SYM(rb_intern("write_bytes")), INT2NUM(stats[i].write_bytes/1024));
    rb_hash_aset(info, ID2SYM(rb_intern("systime")), INT2NUM(stats[i].systime));

    VALUE time_now;
    time_now = rb_funcall(rb_cTime, rb_intern("now"), 0);
    rb_hash_aset(info, ID2SYM(rb_intern("last_call")), rb_funcall(time_now, rb_intern("-"), 1, INT2NUM(stats[i].systime)));

    rb_ary_push(arr, info);
  }

  return arr;
}

static VALUE statgrab_fs_stats(VALUE self) {
  int entries, i;
  sg_fs_stats *stats;
  VALUE arr, info;

  stats = sg_get_fs_stats(&entries);
  if(stats==NULL)
    statgrab_handle_error();

  arr = rb_ary_new();
  for(i = 0; i < entries; i++) {
    info = rb_hash_new();
    rb_hash_aset(info, ID2SYM(rb_intern("device_name")), rb_str_new2(stats[i].device_name));
    rb_hash_aset(info, ID2SYM(rb_intern("fs_type")), rb_str_new2(stats[i].fs_type));
    rb_hash_aset(info, ID2SYM(rb_intern("mnt_point")), rb_str_new2(stats[i].mnt_point));
    rb_hash_aset(info, ID2SYM(rb_intern("size")), INT2NUM(stats[i].size/1024));
    rb_hash_aset(info, ID2SYM(rb_intern("used")), INT2NUM(stats[i].used/1024));
    rb_hash_aset(info, ID2SYM(rb_intern("avail")), INT2NUM(stats[i].avail/1024));
    rb_hash_aset(info, ID2SYM(rb_intern("total_inodes")), INT2NUM(stats[i].total_inodes));
    rb_hash_aset(info, ID2SYM(rb_intern("used_inodes")), INT2NUM(stats[i].used_inodes));
    rb_hash_aset(info, ID2SYM(rb_intern("free_inodes")), INT2NUM(stats[i].free_inodes));
    rb_hash_aset(info, ID2SYM(rb_intern("avail_blocks")), INT2NUM(stats[i].avail_blocks));
    rb_hash_aset(info, ID2SYM(rb_intern("io_size")), INT2NUM(stats[i].io_size));
    rb_hash_aset(info, ID2SYM(rb_intern("block_size")), INT2NUM(stats[i].block_size));
    rb_hash_aset(info, ID2SYM(rb_intern("total_blocks")), INT2NUM(stats[i].total_blocks));
    rb_hash_aset(info, ID2SYM(rb_intern("free_blocks")), INT2NUM(stats[i].free_blocks));
    rb_hash_aset(info, ID2SYM(rb_intern("used_blocks")), INT2NUM(stats[i].used_blocks));
    rb_hash_aset(info, ID2SYM(rb_intern("avail_blocks")), INT2NUM(stats[i].avail_blocks));

    rb_ary_push(arr, info);
  }

  return arr;
}

void Init_statgrab() {
  cStatgrab = rb_define_class("Statgrab", rb_cObject);
  eStatgrabException = rb_define_class_under(cStatgrab, "Exception", rb_eException);
  eStatgrabAsprintfError = rb_define_class_under(cStatgrab, "AsprintfError", eStatgrabException);
  eStatgrabDevicesError = rb_define_class_under(cStatgrab, "DevicesError", eStatgrabException);
  eStatgrabDevstatGetdevsError = rb_define_class_under(cStatgrab, "DevstatGetdevsError", eStatgrabException);
  eStatgrabDevstatSelectdevsError = rb_define_class_under(cStatgrab, "DevstatSelectdevsError", eStatgrabException);
  eStatgrabDiskinfoError = rb_define_class_under(cStatgrab, "DiskinfoError", eStatgrabException);
  eStatgrabEnoentError = rb_define_class_under(cStatgrab, "EnoentError", eStatgrabException);
  eStatgrabGetifaddrsError = rb_define_class_under(cStatgrab, "GetifaddrsError", eStatgrabException);
  eStatgrabGetmntinfoError = rb_define_class_under(cStatgrab, "GetmntinfoError", eStatgrabException);
  eStatgrabGetpagesizeError = rb_define_class_under(cStatgrab, "GetpagesizeError", eStatgrabException);
  eStatgrabHostError = rb_define_class_under(cStatgrab, "HostError", eStatgrabException);
  eStatgrabKstatDataLookupError = rb_define_class_under(cStatgrab, "KstatDataLookupError", eStatgrabException);
  eStatgrabKstatLookupError = rb_define_class_under(cStatgrab, "KstatLookupError", eStatgrabException);
  eStatgrabKstatOpenError = rb_define_class_under(cStatgrab, "KstatOpenError", eStatgrabException);
  eStatgrabKstatReadError = rb_define_class_under(cStatgrab, "KstatReadError", eStatgrabException);
  eStatgrabKvmGetswapinfoError = rb_define_class_under(cStatgrab, "KvmGetswapinfoError", eStatgrabException);
  eStatgrabKvmOpenfilesError = rb_define_class_under(cStatgrab, "KvmOpenfilesError", eStatgrabException);
  eStatgrabMallocError = rb_define_class_under(cStatgrab, "MallocError", eStatgrabException);
  eStatgrabMemstatusError = rb_define_class_under(cStatgrab, "MemstatusError", eStatgrabException);
  eStatgrabOpenError = rb_define_class_under(cStatgrab, "OpenError", eStatgrabException);
  eStatgrabOpendirError = rb_define_class_under(cStatgrab, "OpendirError", eStatgrabException);
  eStatgrabParseError = rb_define_class_under(cStatgrab, "ParseError", eStatgrabException);
  eStatgrabPdhaddError = rb_define_class_under(cStatgrab, "PdhaddError", eStatgrabException);
  eStatgrabPdhcollectError = rb_define_class_under(cStatgrab, "PdhcollectError", eStatgrabException);
  eStatgrabPdhopenError = rb_define_class_under(cStatgrab, "PdhopenError", eStatgrabException);
  eStatgrabPdhreadError = rb_define_class_under(cStatgrab, "PdhreadError", eStatgrabException);
  eStatgrabPermissionError = rb_define_class_under(cStatgrab, "PermissionError", eStatgrabException);
  eStatgrabPstatError = rb_define_class_under(cStatgrab, "PstatError", eStatgrabException);
  eStatgrabSetegidError = rb_define_class_under(cStatgrab, "SetegidError", eStatgrabException);
  eStatgrabSeteuidError = rb_define_class_under(cStatgrab, "SeteuidError", eStatgrabException);
  eStatgrabSetmntentError = rb_define_class_under(cStatgrab, "SetmntentError", eStatgrabException);
  eStatgrabSocketError = rb_define_class_under(cStatgrab, "SocketError", eStatgrabException);
  eStatgrabSwapctlError = rb_define_class_under(cStatgrab, "SwapctlError", eStatgrabException);
  eStatgrabSysconfError = rb_define_class_under(cStatgrab, "SysconfError", eStatgrabException);
  eStatgrabSysctlError = rb_define_class_under(cStatgrab, "SysctlError", eStatgrabException);
  eStatgrabSysctlbynameError = rb_define_class_under(cStatgrab, "SysctlbynameError", eStatgrabException);
  eStatgrabSysctlnametomibError = rb_define_class_under(cStatgrab, "SysctlnametomibError", eStatgrabException);
  eStatgrabUnameError = rb_define_class_under(cStatgrab, "UnameError", eStatgrabException);
  eStatgrabUnsupportedError = rb_define_class_under(cStatgrab, "UnsupportedError", eStatgrabException);
  eStatgrabXswVerMismatchError = rb_define_class_under(cStatgrab, "XswVerMismatchError", eStatgrabException);
  rb_define_method(cStatgrab, "initialize", statgrab_initialize, -2);
  rb_define_method(cStatgrab, "cpu_stats", statgrab_cpu_stats, 0);
  rb_define_method(cStatgrab, "cpu", statgrab_cpu_stats, 0);
  rb_define_method(cStatgrab, "cpu_stats_diff", statgrab_cpu_stats_diff, 0);
  rb_define_method(cStatgrab, "cpu_difference", statgrab_cpu_stats_diff, 0);
  rb_define_method(cStatgrab, "cpu_percents", statgrab_cpu_percents, 0);
  rb_define_method(cStatgrab, "disk_io_stats", statgrab_disk_io_stats, 0);
  rb_define_method(cStatgrab, "disk_io", statgrab_disk_io_stats, 0);
  rb_define_method(cStatgrab, "disk_io_stats_diff", statgrab_disk_io_stats_diff, 0);
  rb_define_method(cStatgrab, "disk_io_difference", statgrab_disk_io_stats_diff, 0);
  rb_define_method(cStatgrab, "fs_stats", statgrab_fs_stats, 0);
  rb_define_method(cStatgrab, "fs", statgrab_fs_stats, 0);
  rb_define_method(cStatgrab, "file_system", statgrab_fs_stats, 0);
}
