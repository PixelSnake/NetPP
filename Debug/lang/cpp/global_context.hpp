template <class TClass, class TInterface>
class PackageFactory
{
public:
	static TInterface * Decode(char * data) { return TClass::Decode(data); }
};

class IPackage {};

[[PACKAGE_DEFS]]