#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <network/WebSocket.h>
#include "cocos2d.h"

#include "extensions/cocos-ext.h"

#include <SocketIO.h>


using namespace std;
using namespace cocos2d::network;
using namespace cocos2d::ui;


typedef cocos2d::network::WebSocket WebSocket;

using namespace cocos2d::ui;

class HelloWorld : public cocos2d::Layer, public cocos2d::network::WebSocket::Delegate, public SocketIO::SIODelegate
{
public:
    
    virtual ~HelloWorld();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    //webSocket
    virtual void onOpen(cocos2d::network::WebSocket* ws);
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    virtual void onClose(cocos2d::network::WebSocket* ws);
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
    void sendMessage(float dt);
    
    
    // socket.io eventのevent listener
    void onReceiveEvent(SIOClient* client , const std::string& data);
    
    // SIODelegate
    virtual void onConnect(SIOClient* client);
    virtual void onMessage(SIOClient* client, const std::string& data);
    virtual void onClose(SIOClient* client);
    virtual void onError(SIOClient* client, const std::string& data);
    
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
    WebSocket* websocket;
    cocos2d::LabelTTF* status;
    SIOClient* _client;
};

#endif // __HELLOWORLD_SCENE_H__
