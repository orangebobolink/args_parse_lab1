namespace types
{
	template<typename T>
	struct Result {
		bool success;
		T data;
		std::string message;
	};
}