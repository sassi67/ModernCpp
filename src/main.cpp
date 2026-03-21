#include <utils/smoke.h>
#include <fmt/core.h>

int main(int argc, char *argv[]) {
    auto message = utils::Smoke::getHello();
    fmt::print("{}", message);
    return 0;
}