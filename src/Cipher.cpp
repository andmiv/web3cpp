#include <web3cpp/Cipher.h>

std::string cipher::encrypt(std::string const& plainText, std::string const& password, Error &error) {
  using namespace dev; // operator+ for vectors are defined inside a dev namespace on CommonData.h
  dev::KDF _kdf = dev::KDF::Scrypt;
  json ret;
  dev::bytesSec derivedKey = dev::deriveNewKey(password, _kdf, ret);
  if (derivedKey.empty()) {
    error.setCode(7); // Key derivation failed
    return "";
  }

  ret["cipher"] = "aes-128-ctr";
  dev::SecureFixedHash<16> key(derivedKey, dev::h128::AlignLeft);
  dev::h128 iv = dev::h128::random();
  {
    json params;
    params["iv"] = toHex(iv.ref());
    ret["cipherparams"] = params.dump();
  }

  // cipher text
  dev::bytesConstRef _v(plainText);
  dev::bytes cipherText = encryptSymNoAuth(key, iv, _v);
  if (cipherText.empty()) {
    error.setCode(8); // Key encryption failed.
    return "";
  }
  ret["ciphertext"] = dev::toHex(cipherText);

  // and mac.
  dev::h256 mac = dev::sha3(derivedKey.ref().cropped(16, 16).toBytes() + cipherText);
  ret["mac"] = dev::toHex(mac.ref());

  return ret.dump();
}
