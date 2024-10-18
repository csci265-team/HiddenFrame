import { useEffect, useMemo, useState } from "react";
import { FaMoon, FaSun } from "react-icons/fa";


export function ThemeSwitcher() {

    const [isDark, setIsDark] = useState(true);

    useEffect(() => {
        const isDark = document.documentElement.classList.contains("dark")
        setIsDark(isDark)
    }, [])

    const changeTheme = useMemo(() => {
        document.documentElement.classList.toggle("dark");
        setIsDark(!isDark)
        localStorage.setItem('@app/theme', isDark ? 'dark' : 'light')
    }, [isDark])

    return (<button onClick={() => changeTheme}> {isDark ? <FaMoon /> : <FaSun />} Change theme</button>);
}
