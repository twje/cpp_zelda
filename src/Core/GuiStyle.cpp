#include "Core/GuiStyle.h"
#include "Core/FontManager.h"

GuiStyle::GuiStyle(
    sf::Color backgroundCol,
    sf::Color backgroundHighlightCol,
    sf::Color foregroundCol,
    sf::Color foregroundHighlightCol,
    sf::Color bodyCol,
    sf::Color bodyHighlightCol,
    sf::Color borderCol,
    sf::Color borderHighlightCol,
    sf::Color textCol,
    sf::Color textHighlightCol,
    float borderSize)
    : mBackgroundCol(backgroundCol),
      mBackgroundHighlightCol(backgroundHighlightCol),
      mForegroundCol(foregroundCol),
      mForegroundHighlightCol(foregroundHighlightCol),
      mBodyCol(bodyCol),
      mBodyHighlightCol(bodyHighlightCol),
      mBorderCol(borderCol),
      mBorderHighlightCol(borderHighlightCol),
      mTextCol(textCol),
      mTextHighlightCol(textHighlightCol),
      mBorderSize(borderSize)
{
}

void GuiStyle::InitFont(std::string fontResourceID)
{
  mFontResourceID = fontResourceID;
  mFont = FontManager::GetInstance().GetResource(fontResourceID);
}

// ----------
// Serializer
// ----------
namespace YAML
{
  bool convert<sf::Color>::decode(const Node &node, sf::Color &color)
  {
    if (!node.IsSequence() || node.size() != 4)
      return false;

    color.r = node[0].as<uint8_t>();
    color.g = node[1].as<uint8_t>();
    color.b = node[2].as<uint8_t>();
    color.a = node[3].as<uint8_t>();

    return true;
  }

  Emitter &operator<<(Emitter &out, const sf::Color &v)
  {
    out << YAML::Flow << YAML::BeginSeq;
    out << static_cast<int>(v.r);
    out << static_cast<int>(v.g);
    out << static_cast<int>(v.b);
    out << static_cast<int>(v.a);
    out << YAML::EndSeq;
    return out;
  }
}

void GuiStyleSerializer::Serialize(const GuiStyle &style, const std::string &filePath)
{
  YAML::Emitter emitter;

  emitter << YAML::BeginMap;
  emitter << YAML::Key << "mBackgroundCol" << YAML::Value << style.mBackgroundCol;
  emitter << YAML::Key << "mBackgroundHighlightCol" << YAML::Value << style.mBackgroundHighlightCol;
  emitter << YAML::Key << "mForegroundCol" << YAML::Value << style.mForegroundCol;
  emitter << YAML::Key << "mForegroundHighlightCol" << YAML::Value << style.mForegroundHighlightCol;
  emitter << YAML::Key << "mBodyCol" << YAML::Value << style.mBodyCol;
  emitter << YAML::Key << "mBodyHighlightCol" << YAML::Value << style.mBodyHighlightCol;
  emitter << YAML::Key << "mBorderCol" << YAML::Value << style.mBorderCol;
  emitter << YAML::Key << "mBorderHighlightCol" << YAML::Value << style.mBorderHighlightCol;
  emitter << YAML::Key << "mTextCol" << YAML::Value << style.mTextCol;
  emitter << YAML::Key << "mTextHighlightCol" << YAML::Value << style.mTextHighlightCol;
  emitter << YAML::Key << "mBorderSize" << YAML::Value << style.mBorderSize;
  emitter << YAML::Key << "mFontResourceID" << YAML::Value << style.mFontResourceID;
  emitter << YAML::EndMap;

  std::ofstream file(filePath);
  file << emitter.c_str();
}

void GuiStyleSerializer::Deserialize(GuiStyle &styleOut, const std::string &filePath)
{
  YAML::Node node = YAML::LoadFile(filePath);
  styleOut.mBackgroundCol = node["mBackgroundCol"].as<sf::Color>();
  styleOut.mBackgroundHighlightCol = node["mBackgroundHighlightCol"].as<sf::Color>();
  styleOut.mForegroundCol = node["mForegroundCol"].as<sf::Color>();
  styleOut.mForegroundHighlightCol = node["mForegroundHighlightCol"].as<sf::Color>();
  styleOut.mBodyCol = node["mBodyCol"].as<sf::Color>();
  styleOut.mBodyHighlightCol = node["mBodyHighlightCol"].as<sf::Color>();
  styleOut.mBorderCol = node["mBorderCol"].as<sf::Color>();
  styleOut.mBorderHighlightCol = node["mBorderHighlightCol"].as<sf::Color>();
  styleOut.mTextCol = node["mTextCol"].as<sf::Color>();
  styleOut.mTextHighlightCol = node["mTextHighlightCol"].as<sf::Color>();
  node["mBorderSize"] = node["mBorderSize"].as<float>();

  // Resource dependencies
  styleOut.InitFont(node["mFontResourceID"].as<std::string>());
}