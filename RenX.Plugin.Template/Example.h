/**
 * This file is in the public domain, furnished "as is", without technical
 * support, and with no warranty, express or implied, as to its usefulness for
 * any purpose.
 *
 * Written by Jessica James <jessica.aj@outlook.com>
 */

#if !defined _EXAMPLE_H_HEADER
#define _EXAMPLE_H_HEADER

#include "Jupiter/Plugin.h"
#include "Jupiter/Reference_String.h"
#include "RenX_Plugin.h"

class RenX_TPlugin : public RenX::Plugin
{
public:
	const Jupiter::ReadableString &getName() override { return name; }

private:
	STRING_LITERAL_AS_NAMED_REFERENCE(name, "RenX_TemplatePlugin");
};

#endif // _EXAMPLE_H_HEADER