#ifndef XC_H
#define XC_H

#define X_DECLARE_PRIVATE(Class) 																						\
    inline Class##Data* d_func() { return reinterpret_cast<Class##Data *>(qGetPtrHelper(d_ptr)); } 						\
    inline const Class##Data* d_func() const { return reinterpret_cast<const Class##Data *>(qGetPtrHelper(d_ptr)); }	\
    friend class Class##Data;

#define X_DECLARE_PUBLIC(Class)                                    						\
    inline Class* x_func() { return static_cast<Class *>(x_ptr); } 						\
    inline const Class* x_func() const { return static_cast<const Class *>(x_ptr); }	\
    friend class Class;

#define X_D(Class) Class##Data *d = d_func();
#define X_X(Class) Class *x = x_func();


#define X_DISABLE_COPY(Class) 					\
    Class(const Class &) = delete;				\
    Class &operator=(const Class &) = delete;
	
#define X_ADD_PUBLIC_PROPERTY(type, property, member, getter, setter, notify) 							\
    private:    																						\
        Q_PROPERTY(type property READ getter WRITE setter NOTIFY notify)								\
    private: 																							\
        type member; 																					\
    public: 																							\
        inline type getter() const { return member; } 													\
        inline void setter(const type& var)    															\
        {   																							\
            if(member != var)    																		\
            {   																						\
                member = var;           																\
                emit notify(member);    																\
            }   																						\
        }																								\
		
#define X_ADD_PRIVATE_MEMBER(type, member, getter, setter)		\
	private:													\
		type member;											\
	public:														\
		inline type& getter() const { return member; }			\
		inline void setter(const type& var) { member = var; }



class Xc{
public:
    enum ButtonHint
    {
        WindowNoButtonHint = 0,             // 无按钮
        WindowMinButtonHint = 1,            // 最小化和关闭按钮;
        WindowMaxButtonHint = 2,            // 最小化、最大化按钮;
        WindowCloseButtonHint = 4,          // 关闭按钮;
        WindowMinMaxCloseButtonHint = 7     // 最小化最大化关闭按钮
    };
};

#endif // XC_H
