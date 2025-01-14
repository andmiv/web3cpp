#ifndef CIPHER_H
#define CIPHER_H

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <string>

#include <nlohmann/json.hpp>

#include <web3cpp/Error.h>
#include <web3cpp/devcrypto/SecretStore.h>
#include <web3cpp/devcore/CommonData.h>
#include <web3cpp/devcore/SHA3.h>

using json = nlohmann::ordered_json;

namespace Cipher {
  std::string encrypt(
    std::string const& plainText, std::string const& password, Error& error
  );
  std::string decrypt(
    std::string const& cipherText, std::string const& password, Error& error
  );
}

#endif // CIPHER_H
