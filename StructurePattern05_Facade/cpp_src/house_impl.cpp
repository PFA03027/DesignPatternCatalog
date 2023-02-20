/**
 * @file house_impl.cpp
 * @author PFA03027@nifty.com
 * @brief Implementor class source of Bridge pattern
 * @version 0.1
 * @date 2023-02-19
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Bridgeパターンの実装サンプル
 *
 * このソースファイルは、BridgeパターンのImplementorクラスの実装、およびConcreteImplementorクラスの実装。
 *
 */

#include "house_impl.hpp"

house_impl::house_impl( void )
{
}

house_impl::~house_impl()
{
}

class straw_house : public house_impl {
public:
	straw_house( void )     = default;
	~straw_house() override = default;

	bool IsVulnerableToWind( void ) override
	{
		return true;
	}
	bool IsVulnerableToFire( void ) override
	{
		return true;
	}
	bool IsThereChimney( void ) override
	{
		return false;
	}
};

class wood_house : public house_impl {
public:
	wood_house( void )     = default;
	~wood_house() override = default;

	bool IsVulnerableToWind( void ) override
	{
		return false;
	}
	bool IsVulnerableToFire( void ) override
	{
		return true;
	}
	bool IsThereChimney( void ) override
	{
		return false;
	}
};

class brick_house : public house_impl {
public:
	brick_house( void )     = default;
	~brick_house() override = default;

	bool IsVulnerableToWind( void ) override
	{
		return false;
	}
	bool IsVulnerableToFire( void ) override
	{
		return false;
	}
	bool IsThereChimney( void ) override
	{
		return true;
	}
};

house_impl* make_house_by_straw( void )
{
	return new straw_house;
}

house_impl* make_house_by_wood( void )
{
	return new wood_house;
}

house_impl* make_house_by_brick( void )
{
	return new brick_house;
}
