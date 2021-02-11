{ name = "lazy"
, dependencies =
  [ "prelude"
  , "foldable-traversable"
  , "invariant"
  , "control"
  , "effect"
  , "assert"
  ]
, packages = ../pure-c/package-sets/packages.dhall
, sources = [ "src/**/*.purs", "test/**/*.purs" ]
}
