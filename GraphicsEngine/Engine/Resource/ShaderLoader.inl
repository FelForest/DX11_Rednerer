namespace GE
{
	template<typename T, typename ...Args, typename std::enable_if<std::is_base_of<Shader, T>::value>::type*>
	inline bool ShaderLoader::Load(std::weak_ptr<T>& outShader, Args ...args)
	{
		// C++ �⺻ RTTI
		auto name = typeid(T).name();
		auto find = shaders.find(name);
		if (find != shaders.end())
		{
			// ������ dynamic�� �´µ� �̰� T�� Shader�� �ڼ��̶�� ���� �����ؾ���
			outShader = std::static_pointer_cast<T>(find->second);
			return true;
		}

		// ������ ���� �� �����ڰ��� �߰��ϰ�, ��ȯ
		std::shared_ptr<Shader> newShader = std::make_shared<T>(args...);
		shaders.insert(std::make_pair(name, newShader));
		outShader = std::static_pointer_cast<T>(newShader);

		return true;
	}
}