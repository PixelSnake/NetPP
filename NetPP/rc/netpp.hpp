template <class TClass, class TInterface>
class PackageFactory
{
public:
	static TInterface * Create(char * data) { return TClass::Decode(data); }
};

class IPackage {};