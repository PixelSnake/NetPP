class PackageDecoder
{
public:
	static IPackage * Decode(char * data)
	{
		int packtype;
		memcpy(&packtype, data, sizeof(int));
		data += sizeof(int);

		[[ALGO_DECODER]]
	}
};