// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYSTEM_INFO_SYSTEM_INFO_LOCALE_H_
#define SYSTEM_INFO_SYSTEM_INFO_LOCALE_H_

#include <glib.h>
#include <string>

#include "common/extension_adapter.h"
#include "common/picojson.h"
#include "common/utils.h"

class SysInfoLocale {
 public:
  static SysInfoLocale& GetSysInfoLocale(ContextAPI* api) {
    static SysInfoLocale instance(api);
    return instance;
  }
  ~SysInfoLocale();
  void Get(picojson::value& error, picojson::value& data);
  inline void StartListen() {
    stopping_ = false;
    g_timeout_add_seconds(3,
                          SysInfoLocale::TimedOutUpdate,
                          static_cast<gpointer>(this));
  }
  inline void StopListen() { stopping_ = true; }

 private:
  explicit SysInfoLocale(ContextAPI* api);
  bool UpdateLanguage();
  bool UpdateCountry();
  static gboolean TimedOutUpdate(gpointer user_data);

  ContextAPI* api_;
  std::string language_;
  std::string country_;
  bool stopping_;

  DISALLOW_COPY_AND_ASSIGN(SysInfoLocale);
};

#endif  // SYSTEM_INFO_SYSTEM_INFO_LOCALE_H_
