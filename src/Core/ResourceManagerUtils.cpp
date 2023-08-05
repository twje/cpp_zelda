#include "Core/ResourceManagerUtils.h"

std::string NormalzeResourceID(const std::string &resourceID)
{
    size_t underscorePos = resourceID.find_last_of('_');
    if (underscorePos != std::string::npos)
    {
        bool isAllDigits = true;
        for (size_t i = underscorePos + 1; i < resourceID.size(); ++i)
        {
            if (!std::isdigit(resourceID[i]))
            {
                isAllDigits = false;
                break;
            }
        }

        if (isAllDigits)
        {
            return resourceID.substr(0, underscorePos);
        }
    }
    return resourceID;
}