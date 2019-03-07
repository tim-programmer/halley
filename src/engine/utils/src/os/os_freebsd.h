/*****************************************************************\
           __
          / /
		 / /                     __  __
		/ /______    _______    / / / / ________   __       __
	   / ______  \  /_____  \  / / / / / _____  | / /      / /
	  / /      | / _______| / / / / / / /____/ / / /      / /
	 / /      / / / _____  / / / / / / _______/ / /      / /
	/ /      / / / /____/ / / / / / / |______  / |______/ /
   /_/      /_/ |________/ / / / /  \_______/  \_______  /
                          /_/ /_/                     / /
			                                         / /
		       High Level Game Framework            /_/

  ---------------------------------------------------------------

  Copyright (c) 2007-2016 - Rodrigo Braz Monteiro.
  This file is subject to the terms of halley_license.txt.

\*****************************************************************/

#pragma once


#if defined(__FreeBSD__) && !defined(__ORBIS__)

#include "os_unix.h"

namespace Halley {
	class OSFreeBSD : public OSUnix {
	public:
		String getUserDataDir() override;
		ComputerData getComputerData() override;
		Path parseProgramPath(const String&) override;

		void openURL(const String& url) override;
	};
}

#endif
