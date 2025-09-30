#include <string>
#include <filesystem>
class Render {

private:
    void WriteConnectivityFile(std::filesystem::path& path );
    void WritePointFile(std::filesystem::path& path);
public:
    void WriteMesh(std::string MeshName,std::filesystem::path path = std::filesystem::path("../Storage/Meshes"));
    void WritePoly(std::string PolyName,std::filesystem::path path = std::filesystem::path("../Storage/Polys"));
    void WritePointLst(std::string PointLstName, std::filesystem::path path = std::filesystem::path("../Storage/PointLsts"));

};