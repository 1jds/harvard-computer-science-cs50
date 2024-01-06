// import { useState, useEffect } from "react";
// import { Link } from "react-router-dom";
// import navLogoDark from "./assets/nav_logo_dark_theme.svg";
// import navLogoLight from "./assets/nav_logo_light_theme.svg";
// import SearchResults from "./SearchResults";
// import SearchIcon from "@mui/icons-material/Search";
// import LightModeIcon from "@mui/icons-material/LightMode";
// import DarkModeIcon from "@mui/icons-material/DarkMode";
// import Badge from "@mui/material/Badge";
// import AccessibilityNewOutlinedIcon from "@mui/icons-material/AccessibilityNewOutlined";

// export default function Navbar(props) {
//   const [badgeStyle, setBadgeStyle] = useState({
//     "& .MuiBadge-badge": {
//       backgroundColor: "#e81c23",
//       color: "#ffffff",
//     },
//   });
//   const [accessabilityColorPickerValue, setAccessabilityColorPickerValue] =
//     useState();
//   const [isAccessabilityDialogActive, setIsAccessabilityDialogActive] =
//     useState(false);
//   // TO CHANGE THE THEME COLOUR FOR COLOUR-BLIND USERS
//   let root = document.documentElement;
//   const changeRootCustomProperty = (property, value) => {
//     root.style.setProperty(property, value);
//   };

//   function toggleAccessabilityDialogActiveState(boolParam) {
//     setIsAccessabilityDialogActive(boolParam);
//   }

//   useEffect(() => {
//     const elementToTrapFocusOn = document.getElementById("accessability-modal");

//     var focusableEls = elementToTrapFocusOn.querySelectorAll("button, input");
//     var firstFocusableEl = focusableEls[0];
//     var lastFocusableEl = focusableEls[focusableEls.length - 1];
//     var KEYCODE_TAB = 9;

//     const handleTrapTab = (e) => {
//       var isTabPressed = e.key === "Tab" || e.keyCode === KEYCODE_TAB;

//       if (!isTabPressed) {
//         return;
//       }

//       if (e.shiftKey) {
//         /* shift + tab */ if (document.activeElement === firstFocusableEl) {
//           lastFocusableEl.focus();
//           e.preventDefault();
//         }
//       } /* tab */ else {
//         if (document.activeElement === lastFocusableEl) {
//           firstFocusableEl.focus();
//           e.preventDefault();
//         }
//       }
//     };

//     elementToTrapFocusOn.addEventListener("keydown", (e) => handleTrapTab(e));

//     return () => {
//       elementToTrapFocusOn.removeEventListener("keydown", (e) =>
//         handleTrapTab(e)
//       );
//     };
//   }, []);
//   // THIS FUNCTION MODIFIED FROM https://hidde.blog/using-javascript-to-trap-focus-in-an-element/

//   return (
//     <div className="navbar">
//       <button
//         aria-label="light or dark theme toggle"
//         onClick={() => {
//           props.setIsDarkMode((prevState) => !prevState);
//         }}
//         className={
//           props.isDarkMode
//             ? "navbar--light-dark-theme-toggle navbar--theme-icon-dark-mode"
//             : "navbar--light-dark-theme-toggle navbar--theme-icon-light-mode"
//         }
//       >
//         {props.isDarkMode ? <DarkModeIcon /> : <LightModeIcon />}
//       </button>

//       <button
//         aria-label="accessability options"
//         className={
//           props.isDarkMode
//             ? "navbar--accessability-options navbar--theme-icon-dark-mode"
//             : "navbar--accessability-options navbar--theme-icon-light-mode"
//         }
//         onClick={() => toggleAccessabilityDialogActiveState(true)}
//       >
//         <AccessibilityNewOutlinedIcon />
//       </button>
//       {/* ACCESSABILITY SETTINGS MODAL START */}
//       <div
//         id="accessability-modal"
//         tabIndex={-1}
//         role="button"
//         onClick={() => toggleAccessabilityDialogActiveState(false)}
//         className={
//           isAccessabilityDialogActive
//             ? "navbar--accessability-dialog-background navbar--accessability-dialog-background-active"
//             : "navbar--accessability-dialog-background"
//         }
//       >
//         <div
//           onClick={(e) => e.stopPropagation()}
//           className={
//             props.isDarkMode
//               ? "navbar--accessability-dialog-container navbar--accessability-dialog-container-dark-mode"
//               : "navbar--accessability-dialog-container"
//           }
//         >
//           <p className="navbar--accessability-dialog-heading">
//             Colour Blindness Settings
//           </p>
//           <p className="navbar--accessability-dialog-explanation">
//             Use the colour selector in this dialog to change the theme color of
//             the website to a color that you can see more easily. If your color
//             blindness is monochromatic, please select medium-gray.
//           </p>
//           <div className="navbar--accesability-dialog-input-box">
//             <label
//               className="navbar--accessability-dialog-input-label"
//               htmlFor="color-picker"
//             >
//               Color
//             </label>
//             <input
//               onChange={(e) => {
//                 setAccessabilityColorPickerValue(e.target.value);
//                 changeRootCustomProperty("--primary-red", e.target.value);
//                 setBadgeStyle({
//                   "& .MuiBadge-badge": {
//                     backgroundColor: e.target.value,
//                     color: "#ffffff",
//                   },
//                 });
//               }}
//               className="navbar--accessability-dialog-color-input"
//               type="color"
//               value={accessabilityColorPickerValue}
//               id="color-picker"
//             />
//           </div>
//           <button
//             className="navbar--accessability-dialog-close-btn"
//             onClick={() => toggleAccessabilityDialogActiveState(false)}
//           >
//             Close Dialog
//           </button>
//         </div>
//       </div>
//       {/* ACCESSABILITY MODAL END */}
//       <div className="navbar--search-area">
//         <form>
//           <div style={{ display: "flex", alignItems: "center" }}>
//             <div
//               className="utility-class--inlineblock"
//               title="Search by an author's first or last name"
//             >
//               <input
//                 onChange={(e) => {
//                   props.setSearchType(e.target.value);
//                 }}
//                 type="radio"
//                 id="author"
//                 name="fav_language"
//                 value="author"
//                 checked={props.searchType === "author"}
//                 title="Search by an author's first or last name"
//               />
//               <label htmlFor="author">Author</label>
//             </div>
//             <div
//               className="utility-class--inlineblock"
//               title="Search for a poem by title"
//             >
//               <input
//                 onChange={(e) => {
//                   props.setSearchType(e.target.value);
//                 }}
//                 type="radio"
//                 id="title"
//                 name="fav_language"
//                 tabIndex="0"
//                 value="title"
//                 checked={props.searchType === "title"}
//               />
//               <label htmlFor="title">Title</label>
//             </div>
//             <div
//               className="utility-class--inlineblock"
//               title="Search by a certain line of poetry"
//             >
//               <input
//                 onChange={(e) => {
//                   props.setSearchType(e.target.value);
//                 }}
//                 type="radio"
//                 id="lines"
//                 name="fav_language"
//                 tabIndex="0"
//                 value="lines"
//                 checked={props.searchType === "lines"}
//               />
//               <label htmlFor="lines">Lines</label>
//             </div>
//             <div
//               className="utility-class--inlineblock"
//               title="Search for poems of a certain line length"
//             >
//               <input
//                 onChange={(e) => {
//                   props.setSearchType(e.target.value);
//                 }}
//                 type="radio"
//                 id="linecount"
//                 name="fav_language"
//                 tabIndex="0"
//                 value="linecount"
//                 checked={props.searchType === "linecount"}
//               />
//               <label htmlFor="linecount">Linecount</label>
//             </div>
//           </div>
//           <div style={{ display: "flex" }}>
//             <input
//               className="search-area--search-input-area"
//               onChange={props.handleSearchTextInput}
//               onKeyDown={(e) => {
//                 e.key === "Enter" && props.handleSearch(e);
//               }}
//               value={props.searchTerm}
//               type="text"
//               placeholder="Search e.g. Keats"
//             />

//             <Link
//               aria-label="click to search for poems"
//               style={{ textDecoration: "none", color: "inherit" }}
//               to="/poems/search"
//               element={<SearchResults />}
//               className="search-area--search-button"
//               onClick={(e) => props.handleSearch(e)}
//               disabled={!props.searchType || !props.searchTerm}
//             >
//               <SearchIcon />
//             </Link>
//           </div>
//         </form>
//       </div>

//       <div>
//         <Link className="navbar--link" to="/">
//           <img
//             src={props.isDarkMode ? navLogoDark : navLogoLight}
//             className="navbar--logo"
//             alt="website logo"
//           />
//         </Link>
//       </div>

//       <div className="navbar--links-collection">
//         <Link className="navbar--link" to="/poems/about">
//           About
//         </Link>
//         <Link className="navbar--link" to="/poems/newsletter">
//           Newsletter
//         </Link>
//         <Link className="navbar--link" to="/poems/learn">
//           Learn
//         </Link>
//         <Link className="navbar--link" to="/poems/create">
//           Create
//         </Link>

//         <Badge
//           aria-label="count of number of poems added to favourites list"
//           sx={badgeStyle}
//           badgeContent={props.favouritesCount}
//         >
//           <Link className="navbar--link" to="/poems/favourites">
//             Favourites
//           </Link>
//         </Badge>
//       </div>
//     </div>
//   );
// }

export default function Navbar(props) {
  return (
    <>
      <div>our wonderful navbar will go here...</div>
    </>
  );
}
