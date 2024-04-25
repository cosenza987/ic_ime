async function main() {
    const queryString = window.location.search;
    
    const urlParams = new URLSearchParams(queryString);
    
    let pokemon = urlParams.get('pokemon');
    
    if(pokemon == null) {
        pokemon = "bulbasaur";
    }

    let language = urlParams.get('language');
    
    if(language == null) {
        language = "en";
    }
    
    const url = "https://pokeapi.co/api/v2/pokemon/" + pokemon;
    const firstResult = await fetch(url);
    if(!firstResult.ok) {
        throw new Error('Invalid Pokemon');
    }
    const firstData = await firstResult.json(); 

    console.log(firstData);

    const speciesResult = await fetch(firstData.species.url);
    const speciesData = await speciesResult.json();

    let getname = "";
    
    document.getElementById("flavor").innerHTML += "<tr><th>Version</th><th>Flavor Text</th></tr>";
    speciesData.flavor_text_entries.forEach(async(entry) => {
        let flavor = "";
        if(entry.language.name.localeCompare(language) == 0){
            const versionResult = await fetch(entry.version.url);
            const versionData = await versionResult.json();
            flavor += "<tr>";
            versionData.names.forEach(name => {
                if(name.language.name.localeCompare(language) == 0) {
                    flavor += "<td>" + name.name + "</td>";
                }
            });
            flavor += "<td>" + entry.flavor_text + "</td></tr>";
        }
        document.getElementById("flavor").innerHTML += flavor;
    });

    speciesData.names.forEach(name => {
        if(name.language.name.localeCompare(language) == 0) {
            getname += name.name;
        }
    });

    document.getElementById("title").innerHTML = getname;
    document.getElementById("getname").innerHTML = getname;

    let image = "";
    image += "<img src='" + firstData.sprites.front_default + "' id='sprite'/>";
    image += "<img src='" + firstData.sprites.back_default + "' id='sprite'/>";
    document.getElementById("images").innerHTML += image;

    image = "";
    image += "<img src='" + firstData.sprites.front_shiny + "' id='sprite'/>";
    image += "<img src='" + firstData.sprites.back_shiny + "' id='sprite'/>";
    document.getElementById("images").innerHTML += image;

    firstData.types.forEach(async(type) => {
        const typeResult = await fetch(type.type.url);
        const typeData = await typeResult.json();
        let types = "";
        typeData.names.forEach(name => {
            if(name.language.name.localeCompare(language) == 0) {
                types += "<tr><td><a class=\"type-icon type-" + typeData.name + "\">" + name.name + "</td></tr>";
            }
        });
        document.getElementById("types").innerHTML += types;
    });

    document.getElementById("moves").innerHTML += "<tr><th>Type</th><th>Name</th><th>Power</th><th>PP</th></tr>";
    firstData.moves.forEach(async(move) => {
        const movesResult = await fetch(move.move.url);
        const movesData = await movesResult.json();
        let moves = "";
        const typeResult = await fetch(movesData.type.url);
        const typeData = await typeResult.json();
        typeData.names.forEach(name => {
            if(name.language.name.localeCompare(language) == 0) {
                moves += "<tr><td><a class=\"type-icon type-" + typeData.name + "\">" + name.name + "</td>";
            }
        });
        movesData.names.forEach(name => {
            if(name.language.name.localeCompare(language) == 0) {
                moves += "<td>" + name.name + "</td>";
            }
        });
        moves += "<td>" + movesData.power + "</td>";
        moves += "<td>" + movesData.pp + "</td></tr>";
        document.getElementById("moves").innerHTML += moves;
    });
    checkUser();
}

main();

// check user logged in

function checkUser() {
    document.getElementById("profile").innerHTML = "<a href=\"../../login/login.html\"> Login </a>"
    $.get('${pageContext.request.contextPath}/myservlet', function (data) {
        if (data == null) {
            document.getElementById("profile").innerHTML = "<a href=\"../../login/login.html\"> Login </a>";
        } else {
            document.getElementById("profile").innerHTML = "<a href=\"../../Profile/?&user=" + data.username + "\">" + data.username + "</a>";
        }
    });
}
