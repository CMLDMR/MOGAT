function fooreposition() {


    console.log("Merhaba Dünya");

    var controlPanelRect = document.getElementById("ControlPanel").getBoundingClientRect();
    var stackPanel = document.getElementById("mContentStack").getBoundingClientRect();

    console.log(controlPanelRect);
    console.log(stackPanel);


}


function relocationFooter(){

    var rect = document.getElementById("footerid").getBoundingClientRect();

    var rootElement = document.getElementById("RootID").getBoundingClientRect();

    console.log(rootElement.top, rootElement.bottom, rootElement.width, rootElement.height );

    console.log(rect.top, rect.bottom, rect.width, rect.height );

    console.log("window Width:  " + window.innerWidth);
    console.log("window Height: " + window.innerHeight);

    var w = window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth;
    var h = window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight;

    console.log("width: " + w + " Height: " + h);

    if( rect.bottom + 3 < h )
    {
        console.log("set position relative");
        document.getElementById("footerid").style.position = "relative";
    }else{
        console.log("set position fixed bottom:0px");
        document.getElementById("footerid").style.bottom = "-3px";
        document.getElementById("footerid").style.position = "relative";
    }
}
