using KIRO2022
using Documenter

DocMeta.setdocmeta!(KIRO2022, :DocTestSetup, :(using KIRO2022); recursive=true)

makedocs(;
    modules=[KIRO2022],
    authors="Léo Baty and contributors",
    repo="https://github.com/BatyLeo/KIRO2022.jl/blob/{commit}{path}#{line}",
    sitename="KIRO2022.jl",
    format=Documenter.HTML(;
        prettyurls=get(ENV, "CI", "false") == "true",
        canonical="https://BatyLeo.github.io/KIRO2022.jl",
        edit_link="main",
        assets=String[],
    ),
    pages=[
        "Home" => "index.md",
    ],
)

deploydocs(;
    repo="github.com/BatyLeo/KIRO2022.jl",
    devbranch="main",
)
