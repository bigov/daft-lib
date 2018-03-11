#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>
#include <SDL2/SDL_net.h>

typedef char charbuf [256];

////////
//
//
class CNet
{
  public:
		static bool Init();
		static void Quit();
};

////////
//
//
class CNetMessage
{
  protected:
		charbuf buffer;
		enum bufstates {
			EMPTY,
			READING,
			WRITING,
			FULL };
		bufstates state;
		void reset();
  public:
		CNetMessage();
		virtual ~CNetMessage() {};
		virtual int NumToLoad();
		virtual size_t NumToUnLoad();
		void LoadBytes(charbuf & inputbuffer, int n);
		void UnLoadBytes(charbuf & destbuffer);
		void finish();
};

////////
//
//
class CIpAddress
{
  private:
		IPaddress m_Ip;
  public:
    CIpAddress();
    CIpAddress (Uint16 port);
    CIpAddress (std::string host, Uint16 port);
    void SetIp (IPaddress sdl_ip);
    bool Ok() const; //True if the object have a port and a host associated
    IPaddress GetIpAddress() const;
    Uint32 GetHost() const;
    Uint16 GetPort() const;
};

////////
//
//
class CTcpSocket
{
	protected:
		TCPsocket m_Socket;		// the TCP socket structure
		SDLNet_SocketSet set; // Used here only to check existing packets
		CTcpSocket(const CTcpSocket &);
		CTcpSocket operator=(const CTcpSocket &);

	public:
		CTcpSocket();
		virtual ~CTcpSocket();
		//set a CTcpSocket object from a existing SDL socket
		virtual void SetSocket (TCPsocket the_sdl_socket);
		bool Ok() const;		// if theres is a TCPsocket associated to the instance
		bool Ready() const; // True if there are bytes ready to be read
		virtual void OnReady();
};

////////
//
//
class CClientSocket;
 
////////
//
//
class CHostSocket : public CTcpSocket
{
	public:
		//create and open a new socket, with an existing CIpAddress object
		CHostSocket (CIpAddress & ip_address);
		//create and open a new socket with the desired port
		CHostSocket (Uint16 port);
		//set a client CTcpSocket object after listening to the port
		bool Accept (CClientSocket&); 
		virtual void OnReady(); //pure virtual
};

////////
//
//
class CClientSocket : public CTcpSocket
{
	private:
		CIpAddress m_RemoteIp; //the CIpAddress object corresponding to the remote host
	public:
		CClientSocket(); //constructor
		CClientSocket (std::string host, Uint16 port); //Create the object and connect to a host, in a given port
		bool Connect (CIpAddress& remoteip); //make a connection to communicate with a remote host
		bool Connect (CHostSocket& the_listener_socket); //make a connection to communicate with a client
		void SetSocket (TCPsocket  the_sdl_socket); //set a CTcpSocket object from an existing SDL_net socket
		CIpAddress getIpAddress () const; //return a CIpAddress object associated to the remote host
		virtual void OnReady(); //pure virtual
		bool Receive(CNetMessage& rData); //receive data and load it into a CNetMessage object
		bool Send (CNetMessage& sData); //send data from a CNetMessage object
};

