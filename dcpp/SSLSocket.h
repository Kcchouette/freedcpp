/*
 * Copyright (C) 2001-2010 Jacek Sieka, arnetheduck on gmail point com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef DCPLUSPLUS_DCPP_SSLSOCKET_H
#define DCPLUSPLUS_DCPP_SSLSOCKET_H

#include "Socket.h"
#include "Singleton.h"

#include "SSL.h"

#ifndef SSL_SUCCESS
#define SSL_SUCCESS 1
#endif

#ifdef YASSL_VERSION
using namespace yaSSL;
#endif

namespace dcpp {

class SSLSocketException : public SocketException {
public:
#ifdef _DEBUG
	SSLSocketException(const string& aError) noexcept : SocketException("SSLSocketException: " + aError) { }
#else //_DEBUG
	SSLSocketException(const string& aError) noexcept : SocketException(aError) { }
#endif // _DEBUG

	virtual ~SSLSocketException() noexcept { }
};

class CryptoManager;

class SSLSocket : public Socket {
public:
	virtual ~SSLSocket() noexcept {}

	virtual void accept(const Socket& listeningSocket);
	virtual void connect(const string& aIp, uint16_t aPort);
	virtual int read(void* aBuffer, int aBufLen);
	virtual int write(const void* aBuffer, int aLen);
	virtual int wait(uint32_t millis, int waitFor);
	virtual void shutdown() noexcept;
	virtual void close() noexcept;

	virtual bool isSecure() const noexcept { return true; }
	virtual bool isTrusted() const noexcept;
	virtual std::string getCipherName() const noexcept;
	virtual std::string getDigest() const noexcept;

	virtual bool waitConnected(uint32_t millis);
	virtual bool waitAccepted(uint32_t millis);


private:
	friend class CryptoManager;

	SSLSocket(SSL_CTX* context);
	SSLSocket(const SSLSocket&);
	SSLSocket& operator=(const SSLSocket&);

	SSL_CTX* ctx;
	ssl::SSL ssl;

	int checkSSL(int ret);
	bool waitWant(int ret, uint32_t millis);
};

} // namespace dcpp

#endif // SSLSOCKET_H
