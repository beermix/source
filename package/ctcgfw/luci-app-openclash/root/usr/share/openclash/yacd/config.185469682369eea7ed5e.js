(window.webpackJsonp=window.webpackJsonp||[]).push([[3],{EeQf:function(e,t,a){"use strict";a.r(t);a("pNMO"),a("TeQF"),a("QWBl"),a("2B1R"),a("+2oP"),a("27RR"),a("FZtP");var n=a("rePB"),r=a("ODXe"),l=a("17x9"),c=a.n(l),o=a("q1tI"),i=a.n(o),s=a("OADI"),u=a("vJea"),p=a("n57c"),b=a("S7Mu"),d=a.n(b),m=a("DKqX"),f=a("/P0+"),v=a("iuhU"),O=a("uLK7"),y=a.n(O);function g(e){var t=e.OptionComponent,a=e.optionPropsList,n=e.selectedIndex,r=e.onChange;return i.a.createElement("div",{className:y.a.root},a.map((function(e,a){var l=Object(v.a)(y.a.item,{[y.a.itemActive]:a===n}),c=function(e){e.preventDefault(),a!==n&&r(a)};return i.a.createElement("div",{key:a,className:l,tabIndex:0,role:"menuitem",onKeyDown:c,onClick:c},i.a.createElement(t,e))})))}g.propTypes={OptionComponent:l.func,optionPropsList:l.array,selectedIndex:l.number,onChange:l.func};var j=a("WfPo"),E=a("hkBY"),w=a("Utih"),h=a("aK+U"),P=a("zouR");function k(e,t){var a=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),a.push.apply(a,n)}return a}function C(e){for(var t=1;t<arguments.length;t++){var a=null!=arguments[t]?arguments[t]:{};t%2?k(Object(a),!0).forEach((function(t){Object(n.a)(e,t,a[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(a)):k(Object(a)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(a,t))}))}return e}var x={legend:{display:!1},scales:{xAxes:[{display:!1}],yAxes:[{display:!1}]}},D=[23e3,35e3,46e3,33e3,9e4,68e3,23e3,45e3],N=[184e3,183e3,196e3,182e3,19e4,186e3,182e3,189e3],I=D;function S(e){var t=e.id,a=P.a.read(),n=Object(o.useMemo)((function(){return{labels:I,datasets:[C(C(C({},P.d),P.b[t].up),{},{data:D}),C(C(C({},P.d),P.b[t].down),{},{data:N})]}}),[t]),r="chart-"+t;return Object(h.a)(a,r,n,null,x),i.a.createElement("div",{style:{width:130,padding:5}},i.a.createElement("canvas",{id:r}))}function L(e,t){var a=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),a.push.apply(a,n)}return a}function A(e){for(var t=1;t<arguments.length;t++){var a=null!=arguments[t]?arguments[t]:{};t%2?L(Object(a),!0).forEach((function(t){Object(n.a)(e,t,a[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(a)):L(Object(a)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(a,t))}))}return e}var R=i.a.useEffect,T=i.a.useState,U=i.a.useCallback,M=i.a.useRef,K=i.a.useMemo,_=[{id:0},{id:1},{id:2},{id:3}],B=[{label:"Global",value:"Global"},{label:"Rule",value:"Rule"},{label:"Direct",value:"Direct"}],W=[{label:"info",value:"info"},{label:"warning",value:"warning"},{label:"error",value:"error"},{label:"debug",value:"debug"},{label:"silent",value:"silent"}],Q=[{key:"port",label:"HTTP Proxy Port"},{key:"socks-port",label:"SOCKS5 Proxy Port"},{key:"mixed-port",label:"Mixed Port"},{key:"redir-port",label:"Redir Port"}],q=Object(j.a)((function(e){return{selectedChartStyleIndex:Object(s.h)(e),latencyTestUrl:Object(s.f)(e),apiConfig:Object(s.c)(e)}}))((function(e){var t=e.dispatch,a=e.configs,n=e.selectedChartStyleIndex,l=e.latencyTestUrl,c=e.apiConfig,o=T(a),b=Object(r.a)(o,2),v=b[0],O=b[1],y=M(a);R((function(){y.current!==a&&O(a),y.current=a}),[a]);var h=U((function(e,t){O(A(A({},v),{},{[e]:t}))}),[v]),P=U((function(e){var a=e;h("allow-lan",a),t(Object(u.e)(c,{"allow-lan":a}))}),[c,t,h]),k=U((function(e){var a=e.target,n=a.name,r=a.value;switch(a.name){case"mode":case"log-level":h(n,r),t(Object(u.e)(c,{[n]:r}));break;case"redir-port":case"socks-port":case"mixed-port":case"port":if(""!==a.value){var l=parseInt(a.value,10);if(l<0||l>65535)return}h(n,r);break;default:return}}),[c,t,h]),C=Object(j.c)(),x=C.selectChartStyleIndex,D=C.updateAppConfig,N=U((function(e){var a=e.target,n=a.name,r=a.value;switch(n){case"port":case"socks-port":case"mixed-port":case"redir-port":var l=parseInt(r,10);if(l<0||l>65535)return;t(Object(u.e)(c,{[n]:l}));break;case"latencyTestUrl":D(n,r);break;default:throw new Error("unknown input name "+n)}}),[c,t,D]),I=K((function(){var e=v.mode;return"string"==typeof e&&e[0].toUpperCase()+e.slice(1)}),[v.mode]);return i.a.createElement("div",null,i.a.createElement(m.a,{title:"Config"}),i.a.createElement("div",{className:d.a.root},Q.map((function(e){return void 0!==v[e.key]?i.a.createElement("div",{key:e.key},i.a.createElement("div",{className:d.a.label},e.label),i.a.createElement(f.b,{name:e.key,value:v[e.key],onChange:k,onBlur:N})):null})),i.a.createElement("div",null,i.a.createElement("div",{className:d.a.label},"Allow LAN"),i.a.createElement(E.a,{name:"allow-lan",checked:v["allow-lan"],onChange:P})),i.a.createElement("div",null,i.a.createElement("div",{className:d.a.label},"Mode"),i.a.createElement(w.a,{options:B,name:"mode",value:I,onChange:k})),i.a.createElement("div",null,i.a.createElement("div",{className:d.a.label},"Log Level"),i.a.createElement(w.a,{options:W,name:"log-level",value:v["log-level"],onChange:k}))),i.a.createElement("div",{className:d.a.sep},i.a.createElement("div",null)),i.a.createElement("div",{className:d.a.section},i.a.createElement("div",null,i.a.createElement("div",{className:d.a.label},"Chart Style"),i.a.createElement(g,{OptionComponent:S,optionPropsList:_,selectedIndex:n,onChange:x})),i.a.createElement("div",{style:{maxWidth:360}},i.a.createElement("div",{className:d.a.label},"Latency Test URL"),i.a.createElement(f.a,{name:"latencyTestUrl",type:"text",value:l,onBlur:N})),i.a.createElement("div",null,i.a.createElement("div",{className:d.a.label},"Action"),i.a.createElement(p.a,{label:"Log out",onClick:s.a}))))}));t.default=Object(j.a)((function(e){return{configs:Object(u.b)(e),apiConfig:Object(s.c)(e)}}))((function(e){var t=e.dispatch,a=e.configs,n=e.apiConfig;return R((function(){t(Object(u.a)(n))}),[t,n]),i.a.createElement(q,{configs:a})}));q.propTypes={configs:c.a.object}},S7Mu:function(e,t,a){e.exports={root:"_2drigWG08z",section:"_3qy5-MPwaw",sep:"_1sbDIR8sCY",label:"_1Hvw0QbyvH"}},uLK7:function(e,t,a){e.exports={root:"_3uy3l7xDdI",item:"_2hwDLKbh5f",itemActive:"_1OeAkW2Cff"}}}]);