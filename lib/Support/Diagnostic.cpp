
#include "Support/Diagnostic.hpp"

std::string Diagnostic::GetSeverityColor() {
	std::string Ret;

	switch (GetSeverity()) {
	case DiagType::Error:
		Ret = "\033[1;31m";
		break;
	case DiagType::Note:
		Ret = "\033[1;36m";
		break;
	case DiagType::Warning:
		Ret = "\033[1;35m";
		break;
	default:
		assert("Invalid DiagType");
	}

	return Ret;
}

std::string Diagnostic::GetMessage() {
	std::string Message = StoredDiagInfo[static_cast<int>(ID)].Text;
	size_t FormatIdx = Message.find("%");

	while (FormatIdx != std::string::npos) {
		int ArgIdx = Message[FormatIdx + 1] - '0';
		assert(ArgIdx < Args.size());

		DiagArgument Arg = GetArgument(ArgIdx);

		switch (Arg.GetKind()) {
		case DiagArgumentKind::StringRef:
			Message.replace(FormatIdx, 2,
				"‘\033[1;37m" + Arg.GetAsStringRef().Str() + "\033[0m’");
			break;

		case DiagArgumentKind::Unsigned:
			Message.replace(FormatIdx, 2,
				"‘\033[1;37m" + std::to_string(Arg.GetAsUnsigned()) + "\033[0m’");
			break;

		case DiagArgumentKind::Integer:
			Message.replace(FormatIdx, 2,
				"‘\033[1;37m" + std::to_string(Arg.GetAsInteger()) + "\033[0m’");
			break;

		default:
			std::cout << "Argument type \"" << (int)Arg.GetKind() << "\" not handled" << std::endl;
			Message.replace(FormatIdx, 2, "_UNHANDLED_");

		}

		FormatIdx = Message.find("%", FormatIdx + 1);
	}

	return Message;
}
