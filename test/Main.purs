module Test.Main where

import Prelude

import Data.Lazy (defer, force)
import Effect (Effect)
import Test.Assert (assertEqual)

main :: Effect Unit
main = do
  let x = defer \_ -> { a: 0 }
  let y = defer \_ -> [1]
  let z = defer \_ -> [2]
  assertEqual { actual: force x, expected: { a: 0 } }
  assertEqual { actual: force (y <> z), expected: [1, 2] }
