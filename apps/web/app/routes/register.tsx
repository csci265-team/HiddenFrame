/* eslint-disable @typescript-eslint/no-explicit-any */
import type { MetaFunction } from "@remix-run/node";
import { PageHeader, Button, Input } from "../components";
import { BASE_API_URL } from "../lib/consts";
import { useState } from "react";
import { useSearchParams } from "@remix-run/react";
// import { useLoaderData } from "@remix-run/react";

export const meta: MetaFunction = () => {
    return [
        { title: "HiddenFrame" },
        { name: "description", content: "Welcome to HiddenFrame!" },
    ];
};

export default function Register() {

    const [loading, setLoading] = useState(false);
    const [searchParams] = useSearchParams();
    const inviteId = searchParams.get("inviteId");

    const register = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        setLoading(true);

        const username = e.currentTarget.username.value;

        const hashedPassword = await crypto.subtle.digest("SHA-256", new TextEncoder().encode(e.currentTarget.password.value));
        const hashedPasswordHex = Array.from(new Uint8Array(hashedPassword)).map(b => b.toString(16).padStart(2, '0')).join('');

        const resp = await fetch(`${BASE_API_URL}/register`, {
            method: "POST",
            body: JSON.stringify({
                inviteId,
                username,
                password: hashedPasswordHex,
            }),
            headers: {
                contentType: "application/json",
            }
        });

        if (resp.ok) {
            window.location.href = "/login";
        } else {
            alert("Failed to upload image.");
            setLoading(false)
        }
    }

    return (
        <div className="flex items-center justify-center h-full">
            <div className="flex flex-col items-center gap-8 h-full">
                <PageHeader />

                <h2 className="text-2xl font-black ">Register</h2>

                <div className="flex flex-col gap-4 p-4">
                    <form className="flex flex-col gap-4 p-4" onSubmit={register}>
                        <Input type="text" id="username" name="username" placeholder="Username" />
                        <Input type="password" id="password" name="password" placeholder="Password" />
                        <Button loading={loading} type="submit">Register</Button>
                    </form>
                </div>
            </div>
        </div>
    );
}
