#include <iostream>
#include <utils/smoke.h>
#include <fmt/core.h>

int main(int argc, char *argv[]) {
    fmt::print(utils::Smoke::getHello());
    return 0;
}