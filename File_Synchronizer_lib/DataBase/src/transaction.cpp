#include "transaction.h"

void Transaction::FormMessage() {
    std::string message;

    message =   "<target>" + target.string() + "</target>\n" +
                "<operation>" + std::to_string(operation) + "</operation>\n" +
                "<machine>" + std::to_string(sourceMachine) + "</machine>\n";

    ITransaction::SetMessage(message);
}

std::tuple<Operation, std::filesystem::path, int> Transaction::GetParams() {
    return {operation, target, sourceMachine};
}

void Transaction::Print(std::ostream &out) {
    out << this->GetMessage();
}
