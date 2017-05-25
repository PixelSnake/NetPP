class PackageDecoder
{
public:
	static IPackage * Decode(char * data)
	{
		int packtype;
		memcpy(&packtype, data, sizeof(int));
		data += sizeof(int);

		switch (packtype)
		{
		[[NPP_FOREACH: PACKAGES]]
		{
			case [[id]]:
				return dynamic_cast<IPackage *>([[name]]::Decode(data));
		}
		}
	}
};