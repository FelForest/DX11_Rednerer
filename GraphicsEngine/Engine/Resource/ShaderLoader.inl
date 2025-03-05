namespace GE
{
	template<typename T, typename ...Args, typename std::enable_if<std::is_base_of<Shader, T>::value>::type*>
	inline bool ShaderLoader::Load(std::weak_ptr<T>& outShader, Args ...args)
	{
		// C++ 기본 RTTI
		auto name = typeid(T).name();
		auto find = shaders.find(name);
		if (find != shaders.end())
		{
			// 원래는 dynamic이 맞는데 이건 T가 Shader의 자손이라는 것을 강제해야함
			outShader = std::static_pointer_cast<T>(find->second);
			return true;
		}

		// 없으면 생성 후 관리자가에 추가하고, 반환
		std::shared_ptr<Shader> newShader = std::make_shared<T>(args...);
		shaders.insert(std::make_pair(name, newShader));
		outShader = std::static_pointer_cast<T>(newShader);

		return true;
	}
}