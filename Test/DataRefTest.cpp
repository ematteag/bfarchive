/*
  Copyright 2014 International Business Machines, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include "BigFix/DataRef.h"
#include "BigFix/Error.h"
#include <gtest/gtest.h>

using namespace BigFix;

TEST( DataRefTest, ConstructNothing )
{
  DataRef empty;

  EXPECT_EQ( 0ul, empty.Length() );
  EXPECT_TRUE( empty.IsEmpty() );
  EXPECT_EQ( 0ul, empty.Start() );
  EXPECT_EQ( 0ul, empty.End() );
}

TEST( DataRefTest, ConstructLiteral )
{
  DataRef hello( "hello" );

  EXPECT_EQ( 5ul, hello.Length() );
  EXPECT_FALSE( hello.IsEmpty() );
  EXPECT_TRUE( memcmp( hello.Start(), "hello", 5 ) == 0 );
  EXPECT_EQ( hello.Start() + 5, hello.End() );
}

TEST( DataRefTest, ConstructString )
{
  std::string helloString( "hello" );
  DataRef hello( helloString );

  EXPECT_EQ( 5ul, hello.Length() );
  EXPECT_FALSE( hello.IsEmpty() );
  EXPECT_TRUE( memcmp( hello.Start(), "hello", 5 ) == 0 );
  EXPECT_EQ( hello.Start() + 5, hello.End() );
}

TEST( DataRefTest, ConstructPointers )
{
  const uint8_t helloBuffer[] = { 'h', 'e', 'l', 'l', 'o' };

  DataRef hello( helloBuffer, helloBuffer + sizeof( helloBuffer ) );

  EXPECT_EQ( 5ul, hello.Length() );
  EXPECT_FALSE( hello.IsEmpty() );
  EXPECT_TRUE( memcmp( hello.Start(), "hello", 5 ) == 0 );
  EXPECT_EQ( hello.Start() + 5, hello.End() );
}

TEST( DataRefTest, Subscript )
{
  DataRef hello( "hello" );

  EXPECT_EQ( 'h', hello[0] );
  EXPECT_EQ( 'o', hello[4] );
  EXPECT_THROW( hello[5], Error );
}

TEST( DataRefTest, Slice )
{
  DataRef hello( "hello" );

  DataRef hel = hello.Slice( 0, 3 );
  DataRef lo = hello.Slice( 3, 2 );

  EXPECT_EQ( 3ul, hel.Length() );
  EXPECT_TRUE( memcmp( hel.Start(), "hel", 3 ) == 0 );

  EXPECT_EQ( 2ul, lo.Length() );
  EXPECT_TRUE( memcmp( lo.Start(), "lo", 2 ) == 0 );
}

TEST( DataRefTest, InvalidSlice )
{
  DataRef hello( "hello" );

  EXPECT_THROW( hello.Slice( 0, 6 ), Error );
  EXPECT_THROW( hello.Slice( 1, 5 ), Error );
  EXPECT_THROW( hello.Slice( 5, 1 ), Error );
}

TEST( DataRefTest, Equals )
{
  EXPECT_TRUE( DataRef() == DataRef() );
  EXPECT_TRUE( DataRef( "hello" ) == DataRef( "hello" ) );
  EXPECT_FALSE( DataRef( "hello" ) == DataRef( "world" ) );
}
