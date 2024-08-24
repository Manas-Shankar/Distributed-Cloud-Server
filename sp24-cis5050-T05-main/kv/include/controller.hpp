#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <optional>

class KV_Controller
{
public:
    KV_Controller();
    ~KV_Controller();

    bool Put(const std::string &row, const std::string &column, const std::string &value);
    std::optional<std::string> Get(const std::string &row, const std::string &column);
    bool Cput(const std::string &row, const std::string &column, const std::string &v1, const std::string &v2);
    bool Delete(const std::string &row, const std::string &column);

private:
};

#endif // CONTROLLER_HPP
