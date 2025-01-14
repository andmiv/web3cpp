#ifndef WEB3_H
#define WEB3_H

#include <string>

#include <nlohmann/json.hpp>

#include <web3cpp/Eth.h>
#include <web3cpp/Utils.h>
#include <web3cpp/Wallet.h>

#include "version.h"

// Main/Umbrella class that houses all modules.

class Web3 {
  private:
    boost::filesystem::path defaultPath;
    Utils::Provider defaultProvider;

  public:
    // Constructor and overloads.
    Web3(Utils::Provider *provider = NULL, boost::filesystem::path *path = NULL);
    Web3(Utils::Provider provider) : Web3(&provider, NULL) {}
    Web3(boost::filesystem::path path): Web3(NULL, &path) {}

    // Getter for provider.
    Utils::Provider* getProvider() { return &this->defaultProvider; }

    // Current version of the library.
    std::string version;

    // The proper objects for other classes.
    Eth eth;
    Wallet wallet;

    // Current available providers.
    std::vector<Utils::Provider> providers;

    // When using Web3 in a compatible browser, it will be set as the current
    // native provider by that browser, otherwise as NULL.
    Utils::Provider givenProvider;

    // Current provider, or NULL if not set.
    Utils::Provider currentProvider;

    // Changes the provider for the given module.
    // When called on the umbrella class it will also set the provider for
    // ALL sub modules EXCEPT bzz, which needs a separate provider at all times.
    bool setProvider(Utils::Provider myProvider);
};

#endif  // WEB3_H
