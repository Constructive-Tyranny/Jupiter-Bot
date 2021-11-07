/**
 * Copyright (C) 2014-2021 Jessica James.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Written by Jessica James <jessica.aj@outlook.com>
 */

#if !defined _RENX_GREETING_H_HEADER
#define _RENX_GREETING_H_HEADER

#include "Jupiter/Plugin.h"
#include "Jupiter/Reference_String.h"
#include "Jupiter/File.h"
#include "Jupiter/String.hpp"
#include "RenX_Plugin.h"

class RenX_GreetingsPlugin : public RenX::Plugin
{
public: // RenX::Plugin
	void RenX_OnJoin(RenX::Server &server, const RenX::PlayerInfo &player) override;

public: // Jupiter::Plugin
	virtual bool initialize() override;
	int OnRehash() override;

private:
	bool m_sendPrivate;
	size_t m_lastLine;
	unsigned int m_sendMode = 0; /** 0 = Send greetings randomly, 1 = Send greetings sequentially, 2 = Send all greetings */
	Jupiter::File m_greetingsFile;
};

#endif // _RENX_GREETING_H_HEADER