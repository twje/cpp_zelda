#include "Core/TextureManager.h"

#include <cassert>

namespace TextureIDGeneratorPresets
{
    std::string ExtractLastDirectoryWithFilename(const fs::path &filePath)
    {
        assert(fs::is_regular_file(filePath));

        std::string filenameWithoutExtension = filePath.stem().string();
        fs::path parentDir = filePath.parent_path();

        fs::path lastDir;
        auto it = parentDir.begin();
        std::advance(it, std::distance(parentDir.begin(), parentDir.end()) - 1);
        lastDir = *it;

        return lastDir.string() + "_" + filenameWithoutExtension;
    }
}