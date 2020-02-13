"foo";                     // foo
"\"foo\""; r#""foo""#;             // "foo"
1 2.1 4 5.8
"foo #\"# bar";
r##"foo #"# bar"##;                // foo #"# bar
0x122
"\x52"; 'R'; r"R";                 // R
"\\x52"; r"\x52";                  // \x52
#EOF