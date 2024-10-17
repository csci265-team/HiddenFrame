import { FaMoon, FaSun } from "react-icons/fa";


export default function ThemeSwitcher() {
    let isDark = document.documentElement.classList.contains("dark")

    const changeTheme = () => {
        document.documentElement.classList.toggle("dark");
        isDark = document.documentElement.classList.contains("dark")
        localStorage.setItem('@app/theme', isDark ? 'dark' : 'light')
    }

    return (
        <button onClick={changeTheme}> {isDark ? <FaMoon /> : <FaSun />} Change theme</button>
    );
}
