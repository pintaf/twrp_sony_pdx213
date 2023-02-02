/*
   Copyright (c) 2015, The Linux Foundation. All rights reserved.
   Copyright (C) 2020 The OmniRom Project.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <fstream>
#include <unistd.h>
#include <android-base/properties.h>
#include <android-base/logging.h>
#include <sys/resource.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#define LTALABEL_PATH "/dev/block/bootdevice/by-name/LTALabel"

using android::base::GetProperty;

void property_override(const std::string& name, const std::string& value)
{
    size_t valuelen = value.size();

    prop_info* pi = (prop_info*) __system_property_find(name.c_str());
    if (pi != nullptr) {
        __system_property_update(pi, value.c_str(), valuelen);
    }
    else {
        int rc = __system_property_add(name.c_str(), name.size(), value.c_str(), valuelen);
        if (rc < 0) {
            LOG(ERROR) << "property_set(\"" << name << "\", \"" << value << "\") failed: "
                       << "__system_property_add failed";
        }
    }
}

void model_property_override(const std::string& device, const std::string& model)
{
    property_override("ro.product.device", device);
    property_override("ro.product.odm.device", device);
    property_override("ro.product.system.device", device);
    property_override("ro.product.vendor.device", device);
    property_override("ro.build.product", device);
    property_override("ro.product.name", device);
    property_override("ro.product.odm.name", device);
    property_override("ro.product.product.device", device);
    property_override("ro.product.product.name", device);
    property_override("ro.product.system.name", device);
    property_override("ro.product.vendor.name", device);
    property_override("ro.product.model", model);
    property_override("ro.product.odm.model", model);
    property_override("ro.product.system.model", model);
    property_override("ro.product.vendor.model", model);
    property_override("ro.product.product.model", model);
}

void vendor_load_properties()
{
  const std::string twrp_name = GetProperty("ro.twrp.device.name", "");
    std::string model;
    if (std::ifstream file = std::ifstream(LTALABEL_PATH, std::ios::binary)) {
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        size_t offset = str.find("Model: ");

        if (offset != std::string::npos) {
            model = str.substr(offset + 7, 5);
        }
    }

    // pdx206 (xperia 5 ii) model
    if (twrp_name == "pdx206") {
      if (model == "XQ-AS42") {
        model_property_override("pdx206", "XQ-AS42");
      } else if (model == "XQ-AS52") {
        model_property_override("pdx206", "XQ-AS52");
      } else if (model == "XQ-AS62") {
        model_property_override("pdx206", "XQ-AS62");
      } else if (model == "XQ-AS72") {
        model_property_override("pdx206", "XQ-AS72");
      } else if (model == "SO-52A") {
        model_property_override("pdx206", "SO-52A");
      } else if (model == "SOG02") {
        model_property_override("pdx206", "SOG02");
      } else if (model == "A002SO") {
        model_property_override("pdx206", "A002SO");
      } 
   } 

   // pdx203 (xperia 1 ii) model
   else if (twrp_name == "pdx203") {
      if (model == "XQ-AT42") {
        model_property_override("pdx203", "XQ-AT42");
      } else if (model == "XQ-AT51") {
        model_property_override("pdx203", "XQ-AT51");
      } else if (model == "XQ-AT62") {
        model_property_override("pdx203", "XQ-AT62");
      } else if (model == "XQ-AT72") {
        model_property_override("pdx203", "XQ-AT72");
      } else if (model == "SO-52A") {
        model_property_override("pdx203", "SO-51A");
      } else if (model == "SOG02") {
        model_property_override("pdx203", "SOG01");
      } 
   } 
   
   // pdx204 (xperia PRO) model
   else if (twrp_name == "pdx204") {
      if (model == "XQ-XQ52") {
        model_property_override("pdx204", "XQ-XQ52");
      } else if (model == "XQ-XQ52") {
        model_property_override("pdx204", "XQ-XQ62");
      } 
   }
}