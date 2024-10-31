import type { Config } from "tailwindcss";

export default {
	content: ["./app/**/{**,.client,.server}/**/*.{js,jsx,ts,tsx}"],
	darkMode: 'selector',
	theme: {
		extend: {
			colors: {
				colors: {
					background: "var(--background)",
					foreground: "var(--foreground)",
					"hf-beige": "#F3E3BF",
					"hf-brown": "#553829"
				},
			},
			fontFamily: {
				sans: ["Outfit"]
			},
			borderRadius: {
				lg: 'var(--radius)',
				md: 'calc(var(--radius) - 2px)',
				sm: 'calc(var(--radius) - 4px)'
			}
		}
	},
	plugins: [require("tailwindcss-animate")],
} satisfies Config;
