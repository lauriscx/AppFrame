#pragma once

namespace Engine {

	typedef __int64		int64;

	typedef size_t		size;

	typedef char		byte;

	namespace Language {
		enum Values {
			UNKNOW,
			NONE,
			EN,
			RU,
			LT,
			JA,
			CH,
			KO,
			SW,
			NO,
			GE,
			DE
		};
	}
	namespace Currency {
		enum Values {
			UNKNOW,
			NONE,
			EUR,
			DOL,
			RUP,
			MXN,
			RUB
		};
	}
}