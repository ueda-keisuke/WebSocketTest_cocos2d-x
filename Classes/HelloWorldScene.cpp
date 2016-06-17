#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include <string>



USING_NS_CC;

using namespace cocostudio::timeline;





HelloWorld::~HelloWorld()
{
    if (websocket)
        websocket->close();
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Layer::init())
        return false;
    
    // ステータスラベル作成
    Size size = Director::getInstance()->getVisibleSize();
    status = LabelTTF::create("Looking for the gateway...", "Arial", 24);
    status->setPosition(Point(size.width / 2, size.height / 2));
    this->addChild(status);
    
    
    // WebSocket生成
//    websocket = new WebSocket();
//    websocket->init(*this, "http://localhost:8000");

    _client = SocketIO::connect("http://localhost:8080", *this);
    _client->on("from_server", CC_CALLBACK_2(HelloWorld::onReceiveEvent, this));
    
    return true;
}


void HelloWorld::onOpen(cocos2d::network::WebSocket* ws)
{
    status->setString("Connected.");

    
    this->schedule(schedule_selector(HelloWorld::sendMessage), 1);
}

void HelloWorld::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
    String *text = String::createWithFormat("response msg: %s", data.bytes);
    status->setString(text->getCString());
}

void HelloWorld::onClose(cocos2d::network::WebSocket* ws)
{
    websocket = nullptr;
    status->setString("Connection closed.");
}

void HelloWorld::onError(WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
    char buf[100] = {0};
    sprintf(buf, "Error code: %d", error);
    status->setString(buf);
}

void HelloWorld::sendMessage(float dt)
{
    static int count = 0;
    char s[128];
    
    sprintf( s, "%d second(s)", count++ );
    
    if (websocket->getReadyState() == WebSocket::State::OPEN)
    {
        websocket->send(s);
    }
}





void HelloWorld::onConnect(SIOClient* client){
    // SocketIO::connect success
}

void HelloWorld::onMessage(SIOClient* client, const std::string& data){
    // SocketIO::send receive
}
void HelloWorld::onClose(SIOClient* client){
    // SocketIO::disconnect success
}
void HelloWorld::onError(SIOClient* client, const std::string& data){
    // SocketIO::failed
}

/**
 * serverからのemit("hello")をここでlisten
 */
void HelloWorld::onReceiveEvent(SIOClient* client , const std::string& data){
    
//    rapidjson::Document doc;
//    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
//    rapidjson::Value &val = doc["args"];
//    std::string value = val[rapidjson::SizeType(0)]["value"].GetString();
    
    status->setString(data.c_str());
};





