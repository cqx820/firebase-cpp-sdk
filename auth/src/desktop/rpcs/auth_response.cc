// Copyright 2017 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "auth/src/desktop/rpcs/auth_response.h"

#include "app/rest/util.h"

namespace firebase {
namespace auth {

AuthError AuthResponse::error_code() const {
  if (IsSuccessful()) {
    return kAuthErrorNone;
  }
  if (!application_data_->error) {
    return kAuthErrorFailure;
  }

  const auto& errors = application_data_->error->errors;
  const std::string error_reason =
      !errors.empty() ? errors[0]->reason : std::string();
  return GetAuthErrorCode(application_data_->error->message, error_reason);
}

bool AuthResponse::IsSuccessful() const {
  return status() == rest::util::HttpSuccess;
}

}  // namespace auth
}  // namespace firebase
