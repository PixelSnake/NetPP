class [[CLASSNAME]] : PackageFactory<[[CLASSNAME]], IPackage>, IPackage
{
	[[PRIVATE_ATTRIBUTES]]
public:
	[[CLASSNAME]]([[CONSTR_PARAMS]])
	{
		[[CONSTR_ASSIGN]]
	}

	~[[CLASSNAME]]() {}

	static [[CLASSNAME]] * Decode(char * data)
	{
		[[ALGO_DECODE]]
	}

	void Send(SOCKET sock)
	{
		[[ALGO_SEND]]
	}
}
